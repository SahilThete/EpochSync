/*
 * EpochSync
 * Application Coordinator
 */

#include "Application.h"

#include "../system/System.h"
#include "../config/ConfigManager.h"
#include "../launcher/Launcher.h"
#include "../network/NetworkManager.h"
#include "../ntp/NTPClient.h"
#include "../rtc/RTCManager.h"
#include "../time/TimeManager.h"
#include "../ui/UIManager.h"

#include "../common/Logger.h"
#include "../common/Modules.h"

static void Application_EnterErrorState(ApplicationState* state, ApplicationState errorState)
{
    if (state != NULL)
    {
        *state = errorState;
    }

    UIManager_SetScreen(UI_SCREEN_ERROR);
}

EpochSyncResult Application_Initialize(void)
{
    Logger_Info(
        MODULE_APPLICATION,
        "Initializing application.");

    EpochSyncResult result;

    result = System_Initialize();

    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "System initialization failed.");

        return result;
    }

    result = TimeManager_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "TimeManager initialization failed.");
        return result;
    }

    result = RTCManager_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "RTCManager initialization failed.");
        return result;
    }

    result = ConfigManager_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "ConfigManager initialization failed.");
        return result;
    }

    result = NetworkManager_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "NetworkManager initialization failed.");
        return result;
    }

    result = NTPClient_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "NTPClient initialization failed.");
        return result;
    }

    result = UIManager_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "UIManager initialization failed.");
        return result;
    }

    result = Launcher_Initialize();
    if (result != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_APPLICATION,
            "Launcher initialization failed.");
        return result;
    }

    Logger_Info(
        MODULE_APPLICATION, 
        "Application initialized.");

    return EPOCHSYNC_SUCCESS;
}

void Application_Run(void)
{
    Logger_Info(
        MODULE_APPLICATION,
        "Starting application runtime.");

    bool running = true;

    ApplicationState state = APPLICATION_STATE_BOOT;
    u32 unixTimeUtc = 0;

    while (running)
    {
        switch (state)
        {
        case APPLICATION_STATE_BOOT:
            UIManager_SetScreen(UI_SCREEN_SPLASH);
            state = APPLICATION_STATE_LOAD_CONFIG;
            break;

        case APPLICATION_STATE_LOAD_CONFIG:
            if (ConfigManager_Load() != EPOCHSYNC_SUCCESS)
            {
                Logger_Warning(
                    MODULE_APPLICATION,
                    "Configuration load failed; using defaults.");
                Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_CONFIG);
            }
            else
            {
                state = APPLICATION_STATE_INIT_NETWORK;
            }
            break;

        case APPLICATION_STATE_INIT_NETWORK:
            if (NetworkManager_Connect() != EPOCHSYNC_SUCCESS)
            {
                Logger_Warning(
                    MODULE_APPLICATION,
                    "Network connection failed.");
                Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_NETWORK);
            }
            else
            {
                UIManager_SetScreen(UI_SCREEN_PROGRESS);
                state = APPLICATION_STATE_CHECK_INTERNET;
            }
            break;

        case APPLICATION_STATE_CHECK_INTERNET:
            if (NetworkManager_IsConnected())
            {
                state = APPLICATION_STATE_FETCH_NTP;
            }
            else
            {
                Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_NETWORK);
            }
            break;

        case APPLICATION_STATE_FETCH_NTP:
            if (NetworkManager_IsConnected())
            {
                if (NTPClient_RequestTime(&unixTimeUtc) == EPOCHSYNC_SUCCESS)
                {
                    state = APPLICATION_STATE_CONFIRM;
                }
                else
                {
                    Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_NTP);
                }
            }
            else
            {
                Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_NETWORK);
            }
            break;

        case APPLICATION_STATE_CONFIRM:
        {
            const EpochSyncConfig* config = ConfigManager_GetConfiguration();
            if (config != NULL && config->ConfirmBeforeWrite)
            {
                UIManager_SetScreen(UI_SCREEN_CONFIRM);
                Logger_Info(
                    MODULE_APPLICATION,
                    "RTC write confirmation requested.");
                state = APPLICATION_STATE_SAVE_CONFIG;
            }
            else
            {
                state = APPLICATION_STATE_COMMIT_RTC;
            }
            break;
        }

        case APPLICATION_STATE_COMMIT_RTC:
        {
            const EpochSyncConfig* config = ConfigManager_GetConfiguration();
            if (config != NULL && config->ConfirmBeforeWrite)
            {
                Logger_Info(
                    MODULE_APPLICATION,
                    "Skipping RTC write until confirmation is handled.");
            }
            else if (RTCManager_WriteUnixTime(unixTimeUtc) != EPOCHSYNC_SUCCESS)
            {
                Application_EnterErrorState(&state, APPLICATION_STATE_ERROR_RTC);
            }
            else
            {
                Logger_Info(
                    MODULE_APPLICATION,
                    "RTC write completed.");
            }
            state = APPLICATION_STATE_SAVE_CONFIG;
            break;
        }

        case APPLICATION_STATE_SAVE_CONFIG:
            if (ConfigManager_Save() != EPOCHSYNC_SUCCESS)
            {
                Logger_Warning(
                    MODULE_APPLICATION,
                    "Configuration save is not implemented yet.");
            }
            state = APPLICATION_STATE_UI;
            break;

        case APPLICATION_STATE_UI:
        {
            /*
            * Idle state.
            *
            * The application remains here until
            * controller input changes the state.
            */
            break;
        }

        case APPLICATION_STATE_LAUNCH:
        {
            const EpochSyncConfig* config = ConfigManager_GetConfiguration();
            if (config != NULL && config->AutoLaunchNextELF && config->NextELF[0] != '\0')
            {
                Logger_Info(
                    MODULE_APPLICATION,
                    "Launching configured ELF.");
                Launcher_Execute(config->NextELF);
            }

            UIManager_SetScreen(UI_SCREEN_MAIN);
            /*
            * Runtime continues.
            * Exit will later be triggered by controller input.
            */
            state = APPLICATION_STATE_UI;
            break;
        }

        case APPLICATION_STATE_ERROR_CONFIG:
        case APPLICATION_STATE_ERROR_NETWORK:
        case APPLICATION_STATE_ERROR_NTP:
        case APPLICATION_STATE_ERROR_RTC:
            Logger_Error(
                MODULE_APPLICATION,
                "Application workflow entered an error state.");
            UIManager_SetScreen(UI_SCREEN_ERROR);
            state = APPLICATION_STATE_ERROR_FATAL;
            break;

        case APPLICATION_STATE_EXIT:
            running = false;
            break;

        default:
            Logger_Error(
                MODULE_APPLICATION,
                "Unknown application state.");
            running = false;
            break;

        if (state == APPLICATION_STATE_ERROR_FATAL)
            {
                running = false;
            }

        UIManager_Update();
        UIManager_Render();
        /*
        * TODO:
        * Synchronize to VBlank.
        */
       WaitVblankStart();

    }
}

void Application_Shutdown(void)
{
    Logger_Info(
        MODULE_APPLICATION,
        "Shutting down application.");

    Launcher_Shutdown();
    UIManager_Shutdown();
    NTPClient_Shutdown();
    NetworkManager_Shutdown();
    ConfigManager_Shutdown();
    RTCManager_Shutdown();
    TimeManager_Shutdown();
    System_Shutdown();
}
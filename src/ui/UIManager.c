/*
 * EpochSync
 * UI Manager
 *
 * Responsible for:
 *  - Screen management
 *  - Rendering
 *  - User interaction
 */

#include "UIManager.h"

#include "../common/Logger.h"
#include "../common/Modules.h"

static bool g_Initialized = false;

static UIScreen g_CurrentScreen = UI_SCREEN_SPLASH;

EpochSyncResult UIManager_Initialize(void)
{
    Logger_Info(
        MODULE_UI,
        "Initializing UI manager.");

    g_Initialized = true;

    g_CurrentScreen = UI_SCREEN_SPLASH;

    Logger_Debug(
        MODULE_UI,
        "UI manager initialized.");

    return EPOCHSYNC_SUCCESS;
}

void UIManager_Shutdown(void)
{
    Logger_Info(
        MODULE_UI,
        "Shutting down UI manager.");

    g_CurrentScreen = UI_SCREEN_SPLASH;

    g_Initialized = false;
}

EpochSyncResult UIManager_SetScreen(UIScreen screen)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_UI,
            "UI manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    if (screen > UI_SCREEN_EXIT)
    {
        Logger_Error(
            MODULE_UI,
            "Invalid UI screen.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    g_CurrentScreen = screen;

    Logger_Debug(
        MODULE_UI,
        "UI screen changed.");

    return EPOCHSYNC_SUCCESS;
}

void UIManager_Render(void)
{
    if (!g_Initialized)
    {
        return;
    }

    /*
     * TODO (Phase 2):
     *
     * Render active screen.
     *
     * Splash
     * Main
     * Progress
     * Confirmation
     * Error
     * Exit
     */
}

void UIManager_Update(void)
{
    if (!g_Initialized)
    {
        return;
    }

    /*
     * TODO (Phase 2):
     *
     * Process controller input.
     * Update menu selection.
     * Handle screen transitions.
     */
}

bool UIManager_IsInitialized(void)
{
    return g_Initialized;
}

UIScreen UIManager_GetScreen(void)
{
    return g_CurrentScreen;
}
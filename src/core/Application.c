/*
 * EpochSync
 * Application Coordinator
 */

#include "Application.h"

#include "../system/System.h"

#include "../common/Logger.h"
#include "../common/Modules.h"

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

    Logger_Info(
        MODULE_APPLICATION,
        "Application initialized.");

    return EPOCHSYNC_SUCCESS;
}

void Application_Run(void)
{
    /*
    * TODO (Phase 2):
    *
    * Main application workflow:
    *
    * 1. Load configuration
    * 2. Initialize network
    * 3. Request NTP time
    * 4. Update RTC
    * 5. Launch configured ELF (optional)
    * 6. Shutdown
    */
}

void Application_Shutdown(void)
{
    Logger_Info(
        MODULE_APPLICATION,
        "Shutting down application.");

    System_Shutdown();
}
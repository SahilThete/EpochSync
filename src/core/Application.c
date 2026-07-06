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

    EpochSyncResult Result;

    Result = System_Initialize();

    if (Result != EPOCHSYNC_SUCCESS)
    {
        return Result;
    }

    return EPOCHSYNC_SUCCESS;
}

void Application_Run(void)
{
    /*
     * Phase 1:
     * Nothing to execute yet.
     *
     * Future:
     * Main application state machine.
     */
}

void Application_Shutdown(void)
{
    Logger_Info(
        MODULE_APPLICATION,
        "Shutting down application.");

    System_Shutdown();
}
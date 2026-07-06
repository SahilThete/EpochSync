/*
 * EpochSync
 * Application Coordinator
 */

#include "Application.h"

#include "../system/System.h"

EpochSyncResult Application_Initialize(void)
{
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
    System_Shutdown();
}
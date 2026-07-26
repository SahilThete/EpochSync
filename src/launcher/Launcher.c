/*
 * EpochSync
 * Launcher Manager
 *
 * Responsible for:
 *  - Validating target ELF
 *  - Executing the next application
 */

#include "Launcher.h"

#include "../common/Logger.h"
#include "../common/Modules.h"

static bool g_Initialized = false;

EpochSyncResult Launcher_Initialize(void)
{
    Logger_Info(
        MODULE_LAUNCHER,
        "Initializing launcher.");

    g_Initialized = true;

    Logger_Debug(
        MODULE_LAUNCHER,
        "Launcher initialized.");

    return EPOCHSYNC_SUCCESS;
}

void Launcher_Shutdown(void)
{
    Logger_Info(
        MODULE_LAUNCHER,
        "Shutting down launcher.");

    g_Initialized = false;
}

EpochSyncResult Launcher_Execute(const char* path)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_LAUNCHER,
            "Launcher not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    if (path == NULL)
    {
        Logger_Error(
            MODULE_LAUNCHER,
            "Launcher_Execute called with NULL path.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    if (path[0] == '\0')
    {
        Logger_Error(
            MODULE_LAUNCHER,
            "Launcher_Execute called with empty path.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    Logger_Info(
        MODULE_LAUNCHER,
        "Executing target ELF.");

    /*
     * TODO (Phase 2):
     *
     * 1. Validate ELF path
     * 2. Verify target file exists
     * 3. Flush CPU caches
     * 4. Shutdown RPC services
     * 5. Shutdown IOP modules (if required)
     * 6. Prepare LoadExecPS2() arguments
     * 7. Execute target ELF
     *
     * NOTE:
     * LoadExecPS2() does not return on success.
     */

    return EPOCHSYNC_SUCCESS;
}

bool Launcher_IsInitialized(void)
{
    return g_Initialized;
}
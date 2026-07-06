/*
 * EpochSync
 * Launcher Manager
 *
 * Responsible for:
 *  - Managing next ELF
 *  - Executing next application
 */

#include "Launcher.h"

#include <string.h>

#include "../common/Logger.h"
#include "../common/Modules.h"

static LauncherConfiguration g_Launcher;

EpochSyncResult Launcher_Initialize(void)
{
    Logger_Info(
        MODULE_LAUNCHER,
        "Initializing launcher.");

    memset(&g_Launcher, 0, sizeof(g_Launcher));

    return EPOCHSYNC_SUCCESS;
}

void Launcher_Shutdown(void)
{
    Logger_Info(
        MODULE_LAUNCHER,
        "Shutting down launcher.");
}

EpochSyncResult Launcher_SetTarget(const char* path)
{
    if (path == NULL)
    {
        Logger_Error(
            MODULE_LAUNCHER,
            "Launcher_SetTarget called with NULL path.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    strncpy(
        g_Launcher.NextELF,
        path,
        EPOCHSYNC_MAX_PATH_LENGTH - 1);

    g_Launcher.NextELF[EPOCHSYNC_MAX_PATH_LENGTH - 1] = '\0';

    Logger_Info(
        MODULE_LAUNCHER,
        "Launcher target set.");

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult Launcher_Execute(void)
{
    Logger_Info(
        MODULE_LAUNCHER,
        "Executing target ELF (simulated).");
    /*
     * Phase 2
     *
     * LoadExecPS2()
     */

    return EPOCHSYNC_SUCCESS;
}

bool Launcher_HasTarget(void)
{
    return (g_Launcher.NextELF[0] != '\0');
}

const char* Launcher_GetTarget(void)
{
    return g_Launcher.NextELF;
}
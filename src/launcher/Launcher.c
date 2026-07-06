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

static LauncherConfiguration g_Launcher;

EpochSyncResult Launcher_Initialize(void)
{
    memset(&g_Launcher, 0, sizeof(g_Launcher));

    return EPOCHSYNC_SUCCESS;
}

void Launcher_Shutdown(void)
{
}

EpochSyncResult Launcher_SetTarget(const char* path)
{
    if (path == NULL)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    strncpy(
        g_Launcher.NextELF,
        path,
        EPOCHSYNC_MAX_PATH_LENGTH - 1);

    g_Launcher.NextELF[EPOCHSYNC_MAX_PATH_LENGTH - 1] = '\0';

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult Launcher_Execute(void)
{
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
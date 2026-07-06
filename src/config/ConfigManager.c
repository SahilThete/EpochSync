/*
 * EpochSync
 * Configuration Manager
 *
 * Responsible for:
 *  - Loading configuration
 *  - Saving configuration
 *  - Providing application settings
 */

#include "ConfigManager.h"

#include "../common/Constants.h"

static bool g_ConfigLoaded = false;

static EpochSyncConfig g_Config;

EpochSyncResult ConfigManager_Initialize(void)
{
    g_ConfigLoaded = false;

    return EPOCHSYNC_SUCCESS;
}

void ConfigManager_Shutdown(void)
{
}

EpochSyncResult ConfigManager_Load(void)
{
    /*
     * Phase 1:
     * Configuration parser not implemented.
     */

    g_ConfigLoaded = true;

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult ConfigManager_Save(void)
{
    /*
     * Phase 1:
     * Configuration writer not implemented.
     */

    return EPOCHSYNC_SUCCESS;
}

bool ConfigManager_IsLoaded(void)
{
    return g_ConfigLoaded;
}

const EpochSyncConfig* ConfigManager_GetConfiguration(void)
{
    return &g_Config;
}
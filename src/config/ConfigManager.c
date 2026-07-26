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

#include <string.h>

#include "../common/Constants.h"
#include "../common/Logger.h"
#include "../common/Modules.h"

static bool g_Initialized = false;
static bool g_ConfigLoaded = false;

static EpochSyncConfig g_Config;

EpochSyncResult ConfigManager_Initialize(void)
{
    Logger_Info(
        MODULE_CONFIG,
        "Initializing configuration manager.");
    
    g_Config.AutoSync = true;
    g_Config.ConfirmBeforeWrite = true;
    g_Config.AutoLaunchNextELF = false;

    g_Config.NextELF[0] = '\0';

    strcpy(g_Config.PreferredServer, "pool.ntp.org");

    g_Initialized = true;
    g_ConfigLoaded = false;

    Logger_Debug(
        MODULE_CONFIG,
        "Configuration manager initialized.");

    return EPOCHSYNC_SUCCESS;
}

void ConfigManager_Shutdown(void)
{
    Logger_Info(
        MODULE_CONFIG,
        "Shutting down configuration manager.");

    g_ConfigLoaded = false;
    g_Initialized = false;
}

EpochSyncResult ConfigManager_Load(void)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_CONFIG,
            "Configuration manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    /*
    * TODO (Phase 2):
    *
    * 1. Open configuration file
    * 2. Parse key/value pairs
    * 3. Validate each setting
    * 4. Apply defaults for missing values
    * 5. Mark configuration loaded
    */

    g_ConfigLoaded = true;

    Logger_Info(
        MODULE_CONFIG,
        "Configuration loaded.");

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult ConfigManager_Save(void)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_CONFIG,
            "Configuration manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    /*
     * Phase 1:
     * Configuration writer not implemented.
     */

    Logger_Info(
        MODULE_CONFIG,
        "Saving configuration (not implemented).");

    return EPOCHSYNC_SUCCESS;
}

bool ConfigManager_IsLoaded(void)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_CONFIG,
            "Configuration manager not initialized.");

        return false;
    }

    return g_ConfigLoaded;
}

bool ConfigManager_IsInitialized(void)
{
    return g_Initialized;
}

const EpochSyncConfig* ConfigManager_GetConfiguration(void)
{
    if (!g_ConfigLoaded)
    {
        Logger_Warning(
            MODULE_CONFIG,
            "Configuration requested before loading.");
    }

    return &g_Config;
}
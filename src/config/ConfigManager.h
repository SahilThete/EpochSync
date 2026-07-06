#ifndef EPOCHSYNC_CONFIG_MANAGER_H
#define EPOCHSYNC_CONFIG_MANAGER_H

#include <stdbool.h>

#include "../common/Constants.h"
#include "../common/Types.h"

/*----------------------------------------------------------
    Configuration Structure
----------------------------------------------------------*/

typedef struct
{
    bool AutoSync;

    bool ConfirmBeforeWrite;

    bool AutoLaunchNextELF;

    char NextELF[EPOCHSYNC_MAX_PATH_LENGTH];

    char PreferredServer[EPOCHSYNC_MAX_SERVER_NAME_LENGTH];

} EpochSyncConfig;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult ConfigManager_Initialize(void);

void ConfigManager_Shutdown(void);

/*----------------------------------------------------------
    Configuration Operations
----------------------------------------------------------*/

EpochSyncResult ConfigManager_Load(void);

EpochSyncResult ConfigManager_Save(void);

/*----------------------------------------------------------
    State Queries
----------------------------------------------------------*/

bool ConfigManager_IsLoaded(void);

const EpochSyncConfig* ConfigManager_GetConfiguration(void);

#endif /* EPOCHSYNC_CONFIG_MANAGER_H */
#ifndef EPOCHSYNC_LAUNCHER_H
#define EPOCHSYNC_LAUNCHER_H

#include <stdbool.h>

#include "../common/Constants.h"
#include "../common/Types.h"

/*----------------------------------------------------------
    Launcher Configuration
----------------------------------------------------------*/

typedef struct
{
    char NextELF[EPOCHSYNC_MAX_PATH_LENGTH];

    bool AutoLaunch;

} LauncherConfiguration;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult Launcher_Initialize(void);

void Launcher_Shutdown(void);

/*----------------------------------------------------------
    Launcher Operations
----------------------------------------------------------*/

EpochSyncResult Launcher_SetTarget(const char* path);

EpochSyncResult Launcher_Execute(void);

/*----------------------------------------------------------
    State Queries
----------------------------------------------------------*/

bool Launcher_HasTarget(void);

const char* Launcher_GetTarget(void);

#endif /* EPOCHSYNC_LAUNCHER_H */
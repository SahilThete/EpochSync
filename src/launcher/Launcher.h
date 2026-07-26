#ifndef EPOCHSYNC_LAUNCHER_H
#define EPOCHSYNC_LAUNCHER_H

#include "../common/Types.h"

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult Launcher_Initialize(void);

void Launcher_Shutdown(void);

/*----------------------------------------------------------
    Launcher Operations
----------------------------------------------------------*/

EpochSyncResult Launcher_Execute(const char* path);

/*----------------------------------------------------------
    State Queries
----------------------------------------------------------*/

bool Launcher_IsInitialized(void);

#endif /* EPOCHSYNC_LAUNCHER_H */
#ifndef EPOCHSYNC_NETWORK_MANAGER_H
#define EPOCHSYNC_NETWORK_MANAGER_H

#include <stdbool.h>

#include "../common/Types.h"

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult NetworkManager_Initialize(void);

void NetworkManager_Shutdown(void);

/*----------------------------------------------------------
    Network Operations
----------------------------------------------------------*/

EpochSyncResult NetworkManager_Connect(void);

EpochSyncResult NetworkManager_Disconnect(void);

NetworkState NetworkManager_GetState(void);

/*----------------------------------------------------------
    State Queries
----------------------------------------------------------*/

bool NetworkManager_IsConnected(void);
bool NetworkManager_IsInitialized(void);

#endif /* EPOCHSYNC_NETWORK_MANAGER_H */
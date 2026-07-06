/*
 * EpochSync
 * Network Manager
 *
 * Responsible for:
 *  - Initializing networking
 *  - Establishing network connectivity
 *  - Managing network state
 */

#include "NetworkManager.h"

static bool g_IsConnected = false;

EpochSyncResult NetworkManager_Initialize(void)
{
    g_IsConnected = false;

    return EPOCHSYNC_SUCCESS;
}

void NetworkManager_Shutdown(void)
{
    g_IsConnected = false;
}

EpochSyncResult NetworkManager_Connect(void)
{
    /*
     * Phase 1:
     * Network stack not implemented.
     */

    g_IsConnected = true;

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NetworkManager_Disconnect(void)
{
    g_IsConnected = false;

    return EPOCHSYNC_SUCCESS;
}

bool NetworkManager_IsConnected(void)
{
    return g_IsConnected;
}
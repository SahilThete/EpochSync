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

#include "../common/Logger.h"
#include "../common/Modules.h"

static bool g_IsConnected = false;

EpochSyncResult NetworkManager_Initialize(void)
{
    Logger_Info(
        MODULE_NETWORK,
        "Initializing network manager.");

    g_IsConnected = false;

    return EPOCHSYNC_SUCCESS;
}

void NetworkManager_Shutdown(void)
{
    Logger_Info(
        MODULE_NETWORK,
        "Shutting down network manager.");

    g_IsConnected = false;
}

EpochSyncResult NetworkManager_Connect(void)
{
    Logger_Info(
        MODULE_NETWORK,
        "Connecting.");

    /*
     * Phase 1:
     * Network stack not implemented.
     */

    if (g_IsConnected)
    {
        Logger_Warning(
            MODULE_NETWORK,
            "Connect called but already connected.");

        return EPOCHSYNC_SUCCESS;
    }

    g_IsConnected = true;

    Logger_Info(
        MODULE_NETWORK,
        "Network connected (simulated).");

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NetworkManager_Disconnect(void)
{
    g_IsConnected = false;

    Logger_Info(
        MODULE_NETWORK,
        "Network disconnected.");

    return EPOCHSYNC_SUCCESS;
}

bool NetworkManager_IsConnected(void)
{
    return g_IsConnected;
}
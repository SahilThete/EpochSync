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
#include "../config/ConfigManager.h"

static bool g_Initialized = false;
static bool g_IsConnected = false;
static NetworkState g_State = NETWORK_STATE_DISCONNECTED;

EpochSyncResult NetworkManager_Initialize(void)
{
    Logger_Info(
        MODULE_NETWORK,
        "Initializing network manager.");
    
    g_Initialized = true;
    g_IsConnected = false;
    g_State = NETWORK_STATE_DISCONNECTED;

    Logger_Debug(
        MODULE_NETWORK,
        "Network manager initialized.");

    return EPOCHSYNC_SUCCESS;
}

void NetworkManager_Shutdown(void)
{
    Logger_Info(
        MODULE_NETWORK,
        "Shutting down network manager.");

    g_IsConnected = false;
    g_Initialized = false;
    g_State = NETWORK_STATE_DISCONNECTED;
}

EpochSyncResult NetworkManager_Connect(void)
{
    Logger_Debug(
        MODULE_NETWORK,
        "Attempting network connection.");

    /*
    * TODO (Phase 2):
    *
    * 1. Reset IOP
    * 2. Load DEV9.IRX
    * 3. Load SMAP.IRX
    * 4. Load NETMAN.IRX
    * 5. Initialize ps2ip
    * 6. Acquire DHCP address
    * 7. Update connection state
    */

    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_NETWORK,
            "Network manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    if (g_IsConnected)
    {
        Logger_Warning(
            MODULE_NETWORK,
            "Connect called but already connected.");

        return EPOCHSYNC_SUCCESS;
    }

    g_IsConnected = true;
    g_State = NETWORK_STATE_CONNECTED;

    Logger_Debug(
        MODULE_NETWORK,
        "Connection state updated.");

    Logger_Info(
        MODULE_NETWORK,
        "Network connected.");

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NetworkManager_Disconnect(void)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_NETWORK,
            "Network manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    g_IsConnected = false;
    g_State = NETWORK_STATE_DISCONNECTED;

    Logger_Info(
        MODULE_NETWORK,
        "Network disconnected.");

    return EPOCHSYNC_SUCCESS;
}

bool NetworkManager_IsConnected(void)
{
    return g_IsConnected;
}

bool NetworkManager_IsInitialized(void)
{
    return g_Initialized;
}

NetworkState NetworkManager_GetState(void)
{
    return g_State;
}
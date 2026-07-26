/*
 * EpochSync
 * NTP Client
 *
 * Responsible for:
 *  - Sending NTP requests
 *  - Receiving responses
 *  - Parsing timestamps
 */

#include "NTPClient.h"

#include <stddef.h>

#include "../common/Logger.h"
#include "../common/Modules.h"
#include "../network/NetworkManager.h"

static bool g_Initialized = false;

typedef struct
{
    u8 li_vn_mode;
    u8 stratum;
    u8 poll;
    u8 precision;

    u32 rootDelay;
    u32 rootDispersion;
    u32 referenceId;

    u32 referenceSeconds;
    u32 referenceFraction;

    u32 originateSeconds;
    u32 originateFraction;

    u32 receiveSeconds;
    u32 receiveFraction;

    u32 transmitSeconds;
    u32 transmitFraction;

} NTPPacket;

EpochSyncResult NTPClient_Initialize(void)
{
    Logger_Info(
        MODULE_NTP,
        "Initializing NTP client.");

    g_Initialized = true;

    Logger_Debug(
        MODULE_NTP,
        "NTP client initialized.");

    return EPOCHSYNC_SUCCESS;
}

void NTPClient_Shutdown(void)
{
    Logger_Info(
        MODULE_NTP,
        "Shutting down NTP client.");

    g_Initialized = false;
}

EpochSyncResult NTPClient_RequestTime(u32* unixTimeUtc)
{
    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_NTP,
            "NTP client not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    if (unixTimeUtc == NULL)
    {
        Logger_Error(
            MODULE_NTP,
            "NTPClient_RequestTime called with NULL pointer.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    Logger_Debug(
        MODULE_NTP,
        "Sending NTP request.");

    /*
    * TODO (Phase 2):
    *
    * 1. Verify NetworkManager_IsConnected()
    * 2. Create UDP socket
    * 3. Build 48-byte NTP request packet
    * 4. Send packet to configured server
    * 5. Receive response
    * 6. Validate packet size
    * 7. Extract transmit timestamp
    * 8. Convert NTP epoch -> Unix epoch
    * 9. Return Unix timestamp
    * 10. Validate stratum
    * 11. Validate leap indicator
    * 12. Reject Kiss-of-Death packets
    * 13. Populate unixTimeUtc
    */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NTPClient_ParseResponse(const void* packet, size_t packetSize, u32* unixTimeUtc)
{
    Logger_Debug(
        MODULE_NTP,
        "Parsing NTP response.");

    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_NTP,
            "NTP client not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    if (packet == NULL || unixTimeUtc == NULL)
    {
        Logger_Error(
            MODULE_NTP,
            "NTPClient_ParseResponse called with invalid arguments.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    if (packetSize < NTP_PACKET_SIZE)
    {
        Logger_Error(
            MODULE_NTP,
            "Invalid NTP packet size.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    /*
     * Phase 2:
     * Decode NTP packet
     */

    return EPOCHSYNC_SUCCESS;
}

bool NTPClient_IsInitialized(void)
{
    return g_Initialized;
}
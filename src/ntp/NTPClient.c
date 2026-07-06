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

static u32 g_UnixTime = 0;

EpochSyncResult NTPClient_Initialize(void)
{
    Logger_Info(
        MODULE_NTP,
        "Initializing NTP client.");

    g_UnixTime = 0;

    return EPOCHSYNC_SUCCESS;
}

void NTPClient_Shutdown(void)
{
    Logger_Info(
        MODULE_NTP,
        "Shutting down NTP client.");
}

EpochSyncResult NTPClient_RequestTime(void)
{
    Logger_Info(
        MODULE_NTP,
        "Requesting time from NTP servers (simulated).");
    /*
     * Phase 2:
     * Create UDP socket
     * Send NTP packet
     * Receive response
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NTPClient_ParseResponse(void)
{
    Logger_Info(
        MODULE_NTP,
        "Parsing NTP response (simulated).");
    /*
     * Phase 2:
     * Decode NTP packet
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult NTPClient_GetUnixTime(u32* unixTime)
{
    if (unixTime == NULL)
    {
        Logger_Error(
            MODULE_NTP,
            "NTPClient_GetUnixTime called with NULL pointer.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    *unixTime = g_UnixTime;

    return EPOCHSYNC_SUCCESS;
}
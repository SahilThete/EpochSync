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

static u32 g_UnixTime = 0;

EpochSyncResult NTPClient_Initialize(void)
{
    g_UnixTime = 0;

    return EPOCHSYNC_SUCCESS;
}

void NTPClient_Shutdown(void)
{
}

EpochSyncResult NTPClient_RequestTime(void)
{
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
        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    *unixTime = g_UnixTime;

    return EPOCHSYNC_SUCCESS;
}
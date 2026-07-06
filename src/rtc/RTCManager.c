/*
 * EpochSync
 * RTC Manager
 *
 * Responsible for:
 *  - Reading PS2 RTC
 *  - Writing PS2 RTC
 *  - Unix time conversion
 */

#include "RTCManager.h"
#include <stddef.h>

static u32 g_UnixTime = 0;

EpochSyncResult RTCManager_Initialize(void)
{
    g_UnixTime = 0;

    return EPOCHSYNC_SUCCESS;
}

void RTCManager_Shutdown(void)
{
}

EpochSyncResult RTCManager_Read(EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    /*
     * Phase 2:
     * Read PS2 RTC
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_Write(const EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    /*
     * Phase 2:
     * Write PS2 RTC
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_SetUnixTime(u32 unixTime)
{
    g_UnixTime = unixTime;

    /*
     * Phase 2:
     * Convert Unix -> RTC
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_GetUnixTime(u32* unixTime)
{
    if (unixTime == NULL)
    {
        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    *unixTime = g_UnixTime;

    return EPOCHSYNC_SUCCESS;
}
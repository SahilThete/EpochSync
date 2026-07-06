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

#include "../common/Logger.h"
#include "../common/Modules.h"

static u32 g_UnixTime = 0;

EpochSyncResult RTCManager_Initialize(void)
{
    Logger_Info(
        MODULE_RTC,
        "Initializing RTC manager.");

    g_UnixTime = 0;

    return EPOCHSYNC_SUCCESS;
}

void RTCManager_Shutdown(void)
{
    Logger_Info(
        MODULE_RTC,
        "Shutting down RTC manager.");
}

EpochSyncResult RTCManager_Read(EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        Logger_Error(
            MODULE_RTC,
            "RTCManager_Read called with NULL pointer.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    Logger_Info(
        MODULE_RTC,
        "Reading RTC (simulated).");

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
        Logger_Error(
            MODULE_RTC,
            "RTCManager_Write called with NULL pointer.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    Logger_Info(
        MODULE_RTC,
        "Writing RTC (simulated).");

    /*
     * Phase 2:
     * Write PS2 RTC
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_SetUnixTime(u32 unixTime)
{
    g_UnixTime = unixTime;

    Logger_Info(
        MODULE_RTC,
        "RTC Unix time set.");

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
        Logger_Error(
            MODULE_RTC,
            "RTCManager_GetUnixTime called with NULL pointer.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    Logger_Info(
        MODULE_RTC,
        "RTC GetUnixTime called.");

    *unixTime = g_UnixTime;

    return EPOCHSYNC_SUCCESS;
}
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
#include <libcdvd.h>
#include <string.h>

#include "../common/Logger.h"
#include "../common/Modules.h"
#include "../time/TimeManager.h"

static bool g_Initialized = false;

EpochSyncResult RTCManager_Initialize(void)
{
    Logger_Info(
        MODULE_RTC,
        "Initializing RTC manager.");

    g_Initialized = true;

    return EPOCHSYNC_SUCCESS;
}

void RTCManager_Shutdown(void)
{
    Logger_Info(
        MODULE_RTC,
        "Shutting down RTC manager.");

    g_Initialized = false;
}

EpochSyncResult RTCManager_Read(EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        Logger_Error(
            MODULE_RTC,
            "RTCManager_Read called with NULL pointer.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    if (!g_Initialized)
    {
        Logger_Error(
            MODULE_RTC,
            "RTC manager not initialized.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    Logger_Debug(
        MODULE_RTC,
        "Reading RTC.");

    /*
    * TODO (Phase 2):
    * 1. Call sceCdReadClock()
    * 2. Validate BCD values using TimeManager_IsValidBCD()
    * 3. Convert BCD -> binary
    * 4. Populate EpochSyncDateTime
    * 5. Validate with TimeManager_IsValidDateTime()
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

    Logger_Debug(
        MODULE_RTC,
        "Writing RTC.");

    /*
     * TODO (Phase 2):
        * Write PS2 RTC
     */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_WriteUnixTime(u32 unixTimeUtc)
{
    EpochSyncDateTime rtcDateTime;

    EpochSyncResult result =
        TimeManager_UnixToRTCDateTime(
            unixTimeUtc,
            &rtcDateTime);

    if (result != EPOCHSYNC_SUCCESS)
    {
        return result;
    }

    Logger_Debug(
        MODULE_RTC,
        "RTC Unix time set.");

    /* TODO (Phase 2):
    * Write rtcDateTime using sceCdWriteClock()
    */

    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult RTCManager_ReadUnixTime(u32* unixTime)
{
    if (unixTime == NULL)
    {
        Logger_Error(
            MODULE_RTC,
            "RTCManager_ReadUnixTime called with NULL pointer.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    Logger_Debug(
        MODULE_RTC,
        "RTC ReadUnixTime called.");

    EpochSyncDateTime rtcDateTime;

    EpochSyncResult result =
        RTCManager_Read(&rtcDateTime);

    if (result != EPOCHSYNC_SUCCESS)
    {
        return result;
    }

    return TimeManager_RTCDateTimeToUnix(
        &rtcDateTime,
        unixTime);
}

EpochSyncResult RTCManager_IsBatteryAvailable(bool* available)
{
    if (available == NULL)
    {
        Logger_Error(
            MODULE_RTC,
            "RTCManager_IsBatteryAvailable called with NULL pointer.");

        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    *available = true;

    Logger_Debug(
        MODULE_RTC,
        "RTC battery availability checked.");

    return EPOCHSYNC_SUCCESS;
}
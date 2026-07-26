/*
 * EpochSync
 * Time Manager
 *
 * Responsible for:
 *  - Unix Epoch <-> calendar (EpochSyncDateTime) conversions
 *  - Unix Epoch <-> PS2 hardware RTC conversions
 *  - BCD <-> binary conversion for RTC register values
 *  - Display-only UTC/timezone offset application
 *  - Leap year / calendar validation
 *  - RTC timestamp formatting
 */

#include "TimeManager.h"

/*----------------------------------------------------------
    Includes
----------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../common/Logger.h"
#include "../common/Modules.h"

/*----------------------------------------------------------
    Private Constants
----------------------------------------------------------*/

#define TIMEMANAGER_MIN_SUPPORTED_YEAR    1970
#define TIMEMANAGER_MAX_SUPPORTED_YEAR    2100

/*----------------------------------------------------------
    Static Variables
----------------------------------------------------------*/

static EpochSyncTimezone g_Timezone = {
    0,
    false,
    "UTC"
};

static bool g_Initialized = false;

/*----------------------------------------------------------
    Private Helpers
----------------------------------------------------------*/

static bool TimeManager_Internal_IsValidDateTimeParts(
    int year,
    int month,
    int day,
    int hour,
    int minute,
    int second)
{
    if (year < TIMEMANAGER_MIN_SUPPORTED_YEAR || year > TIMEMANAGER_MAX_SUPPORTED_YEAR)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (day < 1 || day > TimeManager_DaysInMonth(year, month))
    {
        return false;
    }

    if (hour < 0 || hour > 23)
    {
        return false;
    }

    if (minute < 0 || minute > 59)
    {
        return false;
    }

    if (second < 0 || second > 59)
    {
        return false;
    }

    return true;
}

static bool TimeManager_Internal_ValidateDateTime(
    const EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        return false;
    }

    return TimeManager_Internal_IsValidDateTimeParts(
        (int)dateTime->Year,
        (int)dateTime->Month,
        (int)dateTime->Day,
        (int)dateTime->Hour,
        (int)dateTime->Minute,
        (int)dateTime->Second);
}

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult TimeManager_Initialize(void)
{
    Logger_Info(
        MODULE_TIMEMANAGER,
        "Initializing time manager.");

    g_Timezone.OffsetMinutes = 0;
    g_Timezone.DaylightSaving = false;
    strncpy(g_Timezone.Abbreviation, "UTC", sizeof(g_Timezone.Abbreviation) - 1);
    g_Timezone.Abbreviation[sizeof(g_Timezone.Abbreviation) - 1] = '\0';
    g_Initialized  = true;

    return EPOCHSYNC_SUCCESS;
}

void TimeManager_Shutdown(void)
{
    Logger_Info(
        MODULE_TIMEMANAGER,
        "Shutting down time manager.");

    g_Initialized  = false;
}

/*----------------------------------------------------------
    Calendar Utilities
----------------------------------------------------------*/

bool TimeManager_IsLeapYear(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }

    if (year % 100 == 0)
    {
        return false;
    }

    return (year % 4 == 0);
}

int TimeManager_DaysInMonth(int year, int month)
{
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            return TimeManager_IsLeapYear(year) ? 29 : 28;

        default:
            return 0;
    }
}

bool TimeManager_IsValidDateTime(const EpochSyncDateTime* dateTime)
{
    return TimeManager_Internal_ValidateDateTime(dateTime);
}

/*----------------------------------------------------------
    BCD Helpers
----------------------------------------------------------*/

u8 TimeManager_BinaryToBCD(u8 value)
{
    return (u8)(((value / 10) << 4) | (value % 10));
}

u8 TimeManager_BCDToBinary(u8 value)
{
    return (u8)(((value >> 4) * 10) + (value & 0x0F));
}

bool TimeManager_IsValidBCD(u8 value)
{
    return ((value & 0x0F) <= 9) && ((value >> 4) <= 9);
}

/*----------------------------------------------------------
    Epoch Conversion
----------------------------------------------------------*/

EpochSyncResult TimeManager_DateTimeToUnix(
    const EpochSyncDateTime* dateTime,
    u32* unixTime)
{
    if (unixTime == NULL || !TimeManager_Internal_ValidateDateTime(dateTime))
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    uint64_t totalSeconds = 0;
    int year = (int)dateTime->Year;
    int month = (int)dateTime->Month;
    int day = (int)dateTime->Day;

    for (int currentYear = TIMEMANAGER_MIN_SUPPORTED_YEAR; currentYear < year; ++currentYear)
    {
        totalSeconds += (uint64_t)(TimeManager_IsLeapYear(currentYear) ? 366 : 365) * EPOCHSYNC_SECONDS_PER_DAY;
    }

    for (int currentMonth = 1; currentMonth < month; ++currentMonth)
    {
        totalSeconds += (uint64_t)TimeManager_DaysInMonth(year, currentMonth) * EPOCHSYNC_SECONDS_PER_DAY;
    }

    totalSeconds += (uint64_t)(day - 1) * EPOCHSYNC_SECONDS_PER_DAY;
    totalSeconds += (uint64_t)dateTime->Hour * EPOCHSYNC_SECONDS_PER_HOUR;
    totalSeconds += (uint64_t)dateTime->Minute * EPOCHSYNC_SECONDS_PER_MINUTE;
    totalSeconds += dateTime->Second;

    if (totalSeconds > UINT32_MAX)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    *unixTime = (u32)totalSeconds;
    return EPOCHSYNC_SUCCESS;
}

EpochSyncResult TimeManager_UnixToDateTime(
    u32 unixTime,
    EpochSyncDateTime* dateTime)
{
    if (dateTime == NULL)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    uint64_t totalSeconds = unixTime;
    int days = (int)(totalSeconds / EPOCHSYNC_SECONDS_PER_DAY);
    int secondsInDay = (int)(totalSeconds % EPOCHSYNC_SECONDS_PER_DAY);
    int year = TIMEMANAGER_MIN_SUPPORTED_YEAR;

    while (days >= (TimeManager_IsLeapYear(year) ? 366 : 365))
    {
        days -= TimeManager_IsLeapYear(year) ? 366 : 365;
        ++year;
    }

    int month = 1;
    while (days >= TimeManager_DaysInMonth(year, month))
    {
        days -= TimeManager_DaysInMonth(year, month);
        ++month;
    }

    dateTime->Year = (uint16_t)year;
    dateTime->Month = (uint8_t)month;
    dateTime->Day = (uint8_t)(days + 1);
    dateTime->Hour = (uint8_t)(secondsInDay / EPOCHSYNC_SECONDS_PER_HOUR);
    dateTime->Minute = (uint8_t)((secondsInDay % EPOCHSYNC_SECONDS_PER_HOUR) / EPOCHSYNC_SECONDS_PER_MINUTE);
    dateTime->Second = (uint8_t)(secondsInDay % EPOCHSYNC_SECONDS_PER_MINUTE);

    return EPOCHSYNC_SUCCESS;
}

/*----------------------------------------------------------
    RTC Conversion
----------------------------------------------------------*/

EpochSyncResult TimeManager_UnixToRTCDateTime(
    u32 unixTimeUtc,
    EpochSyncDateTime* rtcDateTime)
{
    if (rtcDateTime == NULL)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    uint64_t adjustedSeconds = (uint64_t)unixTimeUtc + EPOCHSYNC_RTC_HARDWARE_UTC_OFFSET_SECONDS;
    if (adjustedSeconds > UINT32_MAX)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    return TimeManager_UnixToDateTime((u32)adjustedSeconds, rtcDateTime);
}

EpochSyncResult TimeManager_RTCDateTimeToUnix(
    const EpochSyncDateTime* rtcDateTime,
    u32* unixTimeUtc)
{
    if (unixTimeUtc == NULL || !TimeManager_Internal_ValidateDateTime(rtcDateTime))
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    u32 rtcUnixTime = 0;
    EpochSyncResult result = TimeManager_DateTimeToUnix(rtcDateTime, &rtcUnixTime);
    if (result != EPOCHSYNC_SUCCESS)
    {
        return result;
    }

    if (rtcUnixTime < EPOCHSYNC_RTC_HARDWARE_UTC_OFFSET_SECONDS)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    *unixTimeUtc = rtcUnixTime - EPOCHSYNC_RTC_HARDWARE_UTC_OFFSET_SECONDS;
    return EPOCHSYNC_SUCCESS;
}

/*----------------------------------------------------------
    Timezone
----------------------------------------------------------*/

EpochSyncResult TimeManager_ApplyTimezone(
    u32 unixTimeUtc,
    const EpochSyncTimezone* timezone,
    EpochSyncDateTime* localDateTime)
{
    if (timezone == NULL || localDateTime == NULL)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    int64_t offsetSeconds = (int64_t)timezone->OffsetMinutes * EPOCHSYNC_SECONDS_PER_MINUTE;
    if (timezone->DaylightSaving)
    {
        offsetSeconds += EPOCHSYNC_SECONDS_PER_HOUR;
    }

    int64_t adjustedSeconds = (int64_t)unixTimeUtc + offsetSeconds;
    if (adjustedSeconds < 0 || adjustedSeconds > UINT32_MAX)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    return TimeManager_UnixToDateTime((u32)adjustedSeconds, localDateTime);
}

EpochSyncResult TimeManager_SetTimezone(const EpochSyncTimezone* timezone)
{
    if (timezone == NULL || timezone->OffsetMinutes < -720 || timezone->OffsetMinutes > 840)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    memcpy(
        &g_Timezone,
        timezone,
        sizeof(EpochSyncTimezone));

    g_Initialized = true;
    return EPOCHSYNC_SUCCESS;
}

const EpochSyncTimezone* TimeManager_GetTimezone(void)
{
    return &g_Timezone;
}

/*----------------------------------------------------------
    Formatting
----------------------------------------------------------*/

EpochSyncResult TimeManager_Format(
    const EpochSyncDateTime* dateTime,
    TimeManagerFormat format,
    char* buffer,
    size_t bufferSize)
{
    if (buffer == NULL || bufferSize < EPOCHSYNC_MAX_FORMATTED_TIME_LENGTH ||
        !TimeManager_Internal_ValidateDateTime(dateTime))
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    static const char* monthNames[] = {
        "",
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };

    int written = 0;

    switch (format)
    {
        case TIMEMANAGER_FORMAT_ISO8601:
            written = snprintf(
                buffer,
                bufferSize,
                "%04u-%02u-%02u %02u:%02u:%02u",
                dateTime->Year,
                dateTime->Month,
                dateTime->Day,
                dateTime->Hour,
                dateTime->Minute,
                dateTime->Second);
            break;

        case TIMEMANAGER_FORMAT_DATE_ONLY:
            written = snprintf(
                buffer,
                bufferSize,
                "%04u-%02u-%02u",
                dateTime->Year,
                dateTime->Month,
                dateTime->Day);
            break;

        case TIMEMANAGER_FORMAT_TIME_ONLY:
            written = snprintf(
                buffer,
                bufferSize,
                "%02u:%02u:%02u",
                dateTime->Hour,
                dateTime->Minute,
                dateTime->Second);
            break;

        case TIMEMANAGER_FORMAT_DISPLAY_SHORT:
            written = snprintf(
                buffer,
                bufferSize,
                "%02u %s %04u",
                dateTime->Day,
                monthNames[dateTime->Month],
                dateTime->Year);
            break;

        default:
            return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    if (written < 0 || (size_t)written >= bufferSize)
    {
        return EPOCHSYNC_ERROR_INVALID_ARGUMENT;
    }

    return EPOCHSYNC_SUCCESS;
}

#ifndef EPOCHSYNC_TIME_MANAGER_H
#define EPOCHSYNC_TIME_MANAGER_H

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
 *
 * IMPORTANT — PS2 hardware RTC nuance:
 *  The PS2's hardware RTC always stores Japan Standard Time (UTC+9),
 *  regardless of console region or any timezone the user configures.
 *  TimeManager_UnixToRTCDateTime() / TimeManager_RTCDateTimeToUnix()
 *  encode this fixed relationship. TimeManager_ApplyTimezone() is a
 *  completely separate, display-only path and must never be used to
 *  produce a value passed to RTCManager_Write().
 */

#include <stdbool.h>
#include <stddef.h>

#include "../common/Constants.h"
#include "../common/Types.h"
/*----------------------------------------------------------
    Timezone Representation (display only — see note above)
----------------------------------------------------------*/

typedef struct
{
    /* Offset from UTC, in minutes, positive East of Greenwich.
       Valid range: -720 (UTC-12) to +840 (UTC+14). */
    int OffsetMinutes;

    /* Reserved for a future fixed-rule DST addition (Roadmap Phase 6).
       Phase 2 treats this as a flat, non-calendar-aware addition applied
       verbatim when true; no DST start/end rules are evaluated here. */
    bool DaylightSaving;

    /* Short cosmetic display abbreviation, e.g. "IST", "UTC", "PST".
       Never parsed or validated against a real timezone database. */
    char Abbreviation[16];

} EpochSyncTimezone;

/*----------------------------------------------------------
    Formatting
----------------------------------------------------------*/

typedef enum
{
    TIMEMANAGER_FORMAT_ISO8601,        /* 2026-07-26 14:03:00 */
    TIMEMANAGER_FORMAT_DATE_ONLY,      /* 2026-07-26 */
    TIMEMANAGER_FORMAT_TIME_ONLY,      /* 14:03:00 */
    TIMEMANAGER_FORMAT_DISPLAY_SHORT   /* 26 Jul 2026 */

} TimeManagerFormat;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult TimeManager_Initialize(void);

void TimeManager_Shutdown(void);

/*----------------------------------------------------------
    Unix Epoch <-> Calendar Conversions (UTC in, UTC out)
----------------------------------------------------------*/

/* Normalizes a calendar date/time already expressed in UTC into a Unix
   timestamp. Performs full range/leap-year validation. Returns
   EPOCHSYNC_ERROR_INVALID_ARGUMENT for an impossible date (e.g. Feb 30). */
EpochSyncResult TimeManager_DateTimeToUnix(
    const EpochSyncDateTime* dateTime,
    u32* unixTime);

/* Expands a Unix timestamp into a calendar date/time, both in UTC.
   No timezone is applied here; see TimeManager_ApplyTimezone(). */
EpochSyncResult TimeManager_UnixToDateTime(
    u32 unixTime,
    EpochSyncDateTime* dateTime);

/*----------------------------------------------------------
    Unix Epoch <-> PS2 Hardware RTC Conversions
----------------------------------------------------------*/

/* Converts a Unix (UTC) timestamp into the calendar fields the PS2
   hardware RTC expects. The RTC is always JST (UTC+9); this function
   applies that fixed offset internally and is NOT affected by the
   display timezone set via TimeManager_SetTimezone(). */
EpochSyncResult TimeManager_UnixToRTCDateTime(
    u32 unixTimeUtc,
    EpochSyncDateTime* rtcDateTime);

/* Inverse of TimeManager_UnixToRTCDateTime(): interprets a date/time
   read from the hardware RTC as JST and returns the equivalent Unix
   (UTC) timestamp. */
EpochSyncResult TimeManager_RTCDateTimeToUnix(
    const EpochSyncDateTime* rtcDateTime,
    u32* unixTimeUtc);

/*----------------------------------------------------------
    BCD Helpers (PS2 RTC hardware register format)
----------------------------------------------------------*/

/* value must be 0-99; behavior for larger values is undefined. */
u8 TimeManager_BinaryToBCD(u8 value);

/* Does not validate; pair with TimeManager_IsValidBCD() on values read
   back from hardware before trusting them. */
u8 TimeManager_BCDToBinary(u8 value);

/* Returns true only if both nibbles of value are in 0-9. */
bool TimeManager_IsValidBCD(u8 value);

/*----------------------------------------------------------
    Timezone / UTC Offset (display only)
----------------------------------------------------------*/

/* Applies a display timezone to a Unix (UTC) timestamp and returns the
   resulting local calendar date/time. Used only for what EpochSync
   shows on screen or writes to logs; never for what is written to the
   hardware RTC. */
EpochSyncResult TimeManager_ApplyTimezone(
    u32 unixTimeUtc,
    const EpochSyncTimezone* timezone,
    EpochSyncDateTime* localDateTime);

EpochSyncResult TimeManager_SetTimezone(const EpochSyncTimezone* timezone);

const EpochSyncTimezone* TimeManager_GetTimezone(void);

/*----------------------------------------------------------
    Calendar Utilities
----------------------------------------------------------*/

bool TimeManager_IsLeapYear(int year);

/* month is 1-12. Returns 0 for an out-of-range month. */
int TimeManager_DaysInMonth(int year, int month);

/* Full range + calendar validation (month 1-12, day within
   TimeManager_DaysInMonth(), hour 0-23, minute/second 0-59, year within
   a sane supported range). Used internally by every conversion function
   above; exposed so ConfigManager/UIManager can validate user-entered
   values before they reach TimeManager or RTCManager at all. */
bool TimeManager_IsValidDateTime(const EpochSyncDateTime* dateTime);

/*----------------------------------------------------------
    Formatting
----------------------------------------------------------*/

/* Renders dateTime into buffer as a NUL-terminated string. bufferSize
   must be at least EPOCHSYNC_MAX_FORMATTED_TIME_LENGTH. Returns
   EPOCHSYNC_ERROR_INVALID_ARGUMENT if bufferSize is too small or
   dateTime fails TimeManager_IsValidDateTime(). */
EpochSyncResult TimeManager_Format(
    const EpochSyncDateTime* dateTime,
    TimeManagerFormat format,
    char* buffer,
    size_t bufferSize);

#endif /* EPOCHSYNC_TIME_MANAGER_H */
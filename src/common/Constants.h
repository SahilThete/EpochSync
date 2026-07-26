#ifndef EPOCHSYNC_CONSTANTS_H
#define EPOCHSYNC_CONSTANTS_H

/*----------------------------------------------------------
    Project Limits
----------------------------------------------------------*/

#define EPOCHSYNC_MAX_PATH_LENGTH            256
#define EPOCHSYNC_MAX_FILENAME_LENGTH         64
#define EPOCHSYNC_MAX_NTP_SERVERS              8
#define EPOCHSYNC_MAX_SERVER_NAME_LENGTH      64
#define EPOCHSYNC_MAX_LOG_MESSAGE_LENGTH     256

/*----------------------------------------------------------
    Configuration
----------------------------------------------------------*/

#define EPOCHSYNC_CONFIG_FILENAME   "EpochSync.ini"
#define EPOCHSYNC_LOG_FILENAME      "EpochSync.log"

/*----------------------------------------------------------
    Network
----------------------------------------------------------*/

#define EPOCHSYNC_DEFAULT_NTP_PORT          123
#define EPOCHSYNC_DEFAULT_TIMEOUT_MS       5000
#define EPOCHSYNC_DEFAULT_RETRY_COUNT         3

/*----------------------------------------------------------
    Time
----------------------------------------------------------*/

#define EPOCHSYNC_SECONDS_PER_MINUTE             60
#define EPOCHSYNC_MINUTES_PER_HOUR               60
#define EPOCHSYNC_HOURS_PER_DAY                  24

#define EPOCHSYNC_SECONDS_PER_HOUR \
    (EPOCHSYNC_SECONDS_PER_MINUTE * EPOCHSYNC_MINUTES_PER_HOUR)
#define EPOCHSYNC_SECONDS_PER_DAY \
    (EPOCHSYNC_SECONDS_PER_HOUR * EPOCHSYNC_HOURS_PER_DAY)
    
/* PS2 RTC stores Japan Standard Time (UTC +9) */
#define EPOCHSYNC_RTC_HARDWARE_UTC_OFFSET_SECONDS (9 * EPOCHSYNC_SECONDS_PER_HOUR)
/* Maximum formatted string returned by TimeManager_Format() */
#define EPOCHSYNC_MAX_FORMATTED_TIME_LENGTH      64

/*----------------------------------------------------------
    UI
----------------------------------------------------------*/

#define EPOCHSYNC_SCREEN_WIDTH             640
#define EPOCHSYNC_SCREEN_HEIGHT            448

/*----------------------------------------------------------
    Launcher
----------------------------------------------------------*/

#define EPOCHSYNC_DEFAULT_NEXT_ELF ""

#endif /* EPOCHSYNC_CONSTANTS_H */
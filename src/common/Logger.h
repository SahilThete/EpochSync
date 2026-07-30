#ifndef EPOCHSYNC_LOGGER_H
#define EPOCHSYNC_LOGGER_H

#include <stdbool.h>
#include <stdarg.h>

#include "Types.h"

/*----------------------------------------------------------
    Logger Configuration
----------------------------------------------------------*/

typedef struct
{
    bool Enabled;

    LogLevel MinimumLevel;

} LoggerConfiguration;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult Logger_Initialize(void);

void Logger_Shutdown(void);

/*----------------------------------------------------------
    Configuration
----------------------------------------------------------*/

void Logger_Enable(bool enabled);

bool Logger_IsEnabled(void);

void Logger_SetMinimumLevel(LogLevel level);

LogLevel Logger_GetMinimumLevel(void);

/*----------------------------------------------------------
    Logging

    All of the below take a printf-style format string plus
    variadic arguments. The formatted message is truncated to
    EPOCHSYNC_MAX_LOG_MESSAGE_LENGTH (see Constants.h) if too long.

    NOTE: existing call sites that pass a single literal string
    continue to work unchanged, as long as that literal contains
    no '%' characters (none currently do).
----------------------------------------------------------*/

#if defined(__GNUC__)
#define EPOCHSYNC_PRINTF_FORMAT(fmtIndex, argIndex) \
    __attribute__((format(printf, fmtIndex, argIndex)))
#else
#define EPOCHSYNC_PRINTF_FORMAT(fmtIndex, argIndex)
#endif

void Logger_Log(
    LogLevel level,
    const char* module,
    const char* format,
    ...) EPOCHSYNC_PRINTF_FORMAT(3, 4);

void Logger_Debug(
    const char* module,
    const char* format,
    ...) EPOCHSYNC_PRINTF_FORMAT(2, 3);

void Logger_Info(
    const char* module,
    const char* format,
    ...) EPOCHSYNC_PRINTF_FORMAT(2, 3);

void Logger_Warning(
    const char* module,
    const char* format,
    ...) EPOCHSYNC_PRINTF_FORMAT(2, 3);

void Logger_Error(
    const char* module,
    const char* format,
    ...) EPOCHSYNC_PRINTF_FORMAT(2, 3);

#endif /* EPOCHSYNC_LOGGER_H */
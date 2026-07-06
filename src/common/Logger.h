#ifndef EPOCHSYNC_LOGGER_H
#define EPOCHSYNC_LOGGER_H

#include <stdbool.h>

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
----------------------------------------------------------*/

void Logger_Log(
    LogLevel level,
    const char* module,
    const char* message);

void Logger_Debug(
    const char* module,
    const char* message);

void Logger_Info(
    const char* module,
    const char* message);

void Logger_Warning(
    const char* module,
    const char* message);

void Logger_Error(
    const char* module,
    const char* message);

#endif /* EPOCHSYNC_LOGGER_H */
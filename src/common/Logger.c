/*
 * EpochSync
 * Logger
 */

#include "Logger.h"

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <debug.h>

#include "Constants.h"

static LoggerConfiguration g_Logger =
{
    true,
    LOG_LEVEL_INFO
};

static void Logger_LogV(
    LogLevel level,
    const char* module,
    const char* format,
    va_list args)
{
    if (!g_Logger.Enabled)
    {
        return;
    }

    if (module == NULL || format == NULL)
    {
        return;
    }

    if (level < g_Logger.MinimumLevel)
    {
        return;
    }

    char buffer[EPOCHSYNC_MAX_LOG_MESSAGE_LENGTH];

    int written = vsnprintf(buffer, sizeof(buffer), format, args);

    if (written < 0)
    {
        return;
    }

    /* vsnprintf NUL-terminates even on truncation; nothing further to do. */

    const char *levelName = "INFO";

    switch (level)
    {
        case LOG_LEVEL_DEBUG:
            levelName = "DEBUG";
            break;

        case LOG_LEVEL_INFO:
            levelName = "INFO";
            break;

        case LOG_LEVEL_WARNING:
            levelName = "WARN";
            break;

        case LOG_LEVEL_ERROR:
            levelName = "ERROR";
            break;

        default:
            break;
    }

    printf("[%s] [%s] %s\n",
        levelName,
        module,
        buffer);
}

EpochSyncResult Logger_Initialize(void)
{
    g_Logger.Enabled = true;
    g_Logger.MinimumLevel = LOG_LEVEL_INFO;

    return EPOCHSYNC_SUCCESS;
}

void Logger_Shutdown(void)
{
}

void Logger_Enable(bool enabled)
{
    g_Logger.Enabled = enabled;
}

bool Logger_IsEnabled(void)
{
    return g_Logger.Enabled;
}

void Logger_SetMinimumLevel(LogLevel level)
{
    g_Logger.MinimumLevel = level;
}

LogLevel Logger_GetMinimumLevel(void)
{
    return g_Logger.MinimumLevel;
}

void Logger_Log(
    LogLevel level,
    const char* module,
    const char* format,
    ...)
{
    va_list args;
    va_start(args, format);
    Logger_LogV(level, module, format, args);
    va_end(args);
}

void Logger_Debug(
    const char* module,
    const char* format,
    ...)
{
    va_list args;
    va_start(args, format);
    Logger_LogV(LOG_LEVEL_DEBUG, module, format, args);
    va_end(args);
}

void Logger_Info(
    const char* module,
    const char* format,
    ...)
{
    va_list args;
    va_start(args, format);
    Logger_LogV(LOG_LEVEL_INFO, module, format, args);
    va_end(args);
}

void Logger_Warning(
    const char* module,
    const char* format,
    ...)
{
    va_list args;
    va_start(args, format);
    Logger_LogV(LOG_LEVEL_WARNING, module, format, args);
    va_end(args);
}

void Logger_Error(
    const char* module,
    const char* format,
    ...)
{
    va_list args;
    va_start(args, format);
    Logger_LogV(LOG_LEVEL_ERROR, module, format, args);
    va_end(args);
}
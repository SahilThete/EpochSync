/*
 * EpochSync
 * Logger
 */

#include "Logger.h"

#include <stddef.h>
#include <stdio.h>
#include <debug.h>

static LoggerConfiguration g_Logger =
{
    true,
    LOG_LEVEL_INFO
};

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
    const char* message)
{
    if (!g_Logger.Enabled)
    {
        return;
    }

    if (module == NULL)
    {
        return;
    }

    if (message == NULL)
    {
        return;
    }

    if (level < g_Logger.MinimumLevel)
    {
        return;
    }

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
        message);
}

void Logger_Debug(
    const char* module,
    const char* message)
{
    Logger_Log(
        LOG_LEVEL_DEBUG,
        module,
        message);
}

void Logger_Info(
    const char* module,
    const char* message)
{
    Logger_Log(
        LOG_LEVEL_INFO,
        module,
        message);
}

void Logger_Warning(
    const char* module,
    const char* message)
{
    Logger_Log(
        LOG_LEVEL_WARNING,
        module,
        message);
}

void Logger_Error(
    const char* module,
    const char* message)
{
    Logger_Log(
        LOG_LEVEL_ERROR,
        module,
        message);
}
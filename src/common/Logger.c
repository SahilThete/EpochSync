/*
 * EpochSync
 * Logger
 */

#include "Logger.h"
#include <stddef.h>

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

    /*
     * Phase 2
     *
     * Format:
     *
     * [INFO] [Network] Connected.
     *
     * Future outputs:
     *
     * Screen
     * PCSX2 Console
     * EpochSync.log
     */

    (void)level;
    (void)module;
    (void)message;
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
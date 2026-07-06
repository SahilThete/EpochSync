#include "Logger.h"

EpochSyncResult Logger_Initialize(void)
{
    return EPOCHSYNC_SUCCESS;
}

void Logger_Shutdown(void)
{
}

void Logger_Info(const char *message)
{
    (void)message;
}

void Logger_Warning(const char *message)
{
    (void)message;
}

void Logger_Error(const char *message)
{
    (void)message;
}

void Logger_Debug(const char *message)
{
    (void)message;
}
#ifndef EPOCHSYNC_LOGGER_H
#define EPOCHSYNC_LOGGER_H

#include "Types.h"

EpochSyncResult Logger_Initialize(void);

void Logger_Shutdown(void);

void Logger_Info(const char *message);

void Logger_Warning(const char *message);

void Logger_Error(const char *message);

void Logger_Debug(const char *message);

#endif /* EPOCHSYNC_LOGGER_H */
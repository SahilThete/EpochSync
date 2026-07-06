#ifndef EPOCHSYNC_RTC_MANAGER_H
#define EPOCHSYNC_RTC_MANAGER_H

#include "../common/Types.h"

/*----------------------------------------------------------
    RTC Date/Time Structure
----------------------------------------------------------*/

typedef struct
{
    int Year;

    int Month;

    int Day;

    int Hour;

    int Minute;

    int Second;

} EpochSyncDateTime;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult RTCManager_Initialize(void);

void RTCManager_Shutdown(void);

/*----------------------------------------------------------
    RTC Operations
----------------------------------------------------------*/

EpochSyncResult RTCManager_Read(EpochSyncDateTime* dateTime);

EpochSyncResult RTCManager_Write(const EpochSyncDateTime* dateTime);

EpochSyncResult RTCManager_SetUnixTime(u32 unixTime);

EpochSyncResult RTCManager_GetUnixTime(u32* unixTime);

#endif /* EPOCHSYNC_RTC_MANAGER_H */
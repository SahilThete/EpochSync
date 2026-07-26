#ifndef EPOCHSYNC_RTC_MANAGER_H
#define EPOCHSYNC_RTC_MANAGER_H

#include "../common/Types.h"
#include "../time/TimeManager.h"


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

EpochSyncResult RTCManager_ReadUnixTime(u32* unixTime);

EpochSyncResult RTCManager_WriteUnixTime(u32 unixTime);

EpochSyncResult RTCManager_IsBatteryAvailable(bool* available);

#endif /* EPOCHSYNC_RTC_MANAGER_H */
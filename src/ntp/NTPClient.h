#ifndef EPOCHSYNC_NTP_CLIENT_H
#define EPOCHSYNC_NTP_CLIENT_H

#include "../common/Types.h"

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult NTPClient_Initialize(void);

void NTPClient_Shutdown(void);

/*----------------------------------------------------------
    NTP Operations
----------------------------------------------------------*/

EpochSyncResult NTPClient_RequestTime(void);

EpochSyncResult NTPClient_ParseResponse(void);

EpochSyncResult NTPClient_GetUnixTime(u32* unixTime);

#endif /* EPOCHSYNC_NTP_CLIENT_H */
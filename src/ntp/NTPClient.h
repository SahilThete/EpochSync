#ifndef EPOCHSYNC_NTP_CLIENT_H
#define EPOCHSYNC_NTP_CLIENT_H

#include "../common/Types.h"

/* RFC 5905 */
#define NTP_PACKET_SIZE 48

/* UDP */
#define NTP_SERVER_PORT 123

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult NTPClient_Initialize(void);

void NTPClient_Shutdown(void);

bool NTPClient_IsInitialized(void);

/*----------------------------------------------------------
    NTP Operations
----------------------------------------------------------*/

EpochSyncResult NTPClient_RequestTime(u32* unixTimeUtc);

EpochSyncResult NTPClient_ParseResponse(const void* packet, size_t packetSize, u32* unixTimeUtc);

#endif /* EPOCHSYNC_NTP_CLIENT_H */
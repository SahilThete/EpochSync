#ifndef EPOCHSYNC_ERROR_CODES_H
#define EPOCHSYNC_ERROR_CODES_H

/*----------------------------------------------------------
    Generic Errors
----------------------------------------------------------*/

#define ES_ERROR_NONE                     0

#define ES_ERROR_UNKNOWN               1000
#define ES_ERROR_INVALID_ARGUMENT      1001
#define ES_ERROR_NOT_IMPLEMENTED       1002

/*----------------------------------------------------------
    Configuration
----------------------------------------------------------*/

#define ES_ERROR_CONFIG_LOAD           2000
#define ES_ERROR_CONFIG_PARSE          2001
#define ES_ERROR_CONFIG_SAVE           2002

/*----------------------------------------------------------
    File System
----------------------------------------------------------*/

#define ES_ERROR_FILE_OPEN             3000
#define ES_ERROR_FILE_READ             3001
#define ES_ERROR_FILE_WRITE            3002
#define ES_ERROR_FILE_NOT_FOUND        3003

/*----------------------------------------------------------
    Network
----------------------------------------------------------*/

#define ES_ERROR_NETWORK_INIT          4000
#define ES_ERROR_NETWORK_CONNECT       4001
#define ES_ERROR_NETWORK_TIMEOUT       4002
#define ES_ERROR_DNS                  4003
#define ES_ERROR_NTP_REQUEST          4004
#define ES_ERROR_SOCKET               4005

/*----------------------------------------------------------
    RTC
----------------------------------------------------------*/

#define ES_ERROR_RTC_READ             5000
#define ES_ERROR_RTC_WRITE            5001
#define ES_ERROR_RTC_INVALID_TIME     5002

/*----------------------------------------------------------
    Launcher
----------------------------------------------------------*/

#define ES_ERROR_ELF_NOT_FOUND        6000
#define ES_ERROR_ELF_EXECUTE          6001

/*----------------------------------------------------------
    UI
----------------------------------------------------------*/

#define ES_ERROR_UI_INITIALIZE        7000
#define ES_ERROR_UI_RENDER            7001

#endif /* EPOCHSYNC_ERROR_CODES_H */
/*
 * EpochSync
 * Application Coordinator
 */

#include "Application.h"
#include "../system/System.h"

int Application_Start(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    /* Initialize the PS2 runtime */
    if (!System_Initialize())
        return -1;

    /*
     * Future Flow:
     *
     * Config_Load();
     * UI_Initialize();
     * RTC_Read();
     * Network_Initialize();
     * NTP_Synchronize();
     * RTC_Write();
     * Launcher_Execute();
     */

    System_Shutdown();

    return 0;
}
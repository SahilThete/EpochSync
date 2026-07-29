/*
 * EpochSync
 * Main Entry Point
 */

 #include "core/Application.h"
 #include <debug.h>
 #include "common/Logger.h"
 #include "common/Modules.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    init_scr();
    scr_clear();

    Logger_Info(
        MODULE_APPLICATION,
        "Starting EpochSync.");

    if (Application_Initialize() != EPOCHSYNC_SUCCESS)
        return -1;

    Logger_Info(
        MODULE_APPLICATION,
        "Application initialized.");

    Application_Run();

    Application_Shutdown();

    Logger_Info(
        MODULE_APPLICATION,
        "Application exiting.");

    return 0;
}
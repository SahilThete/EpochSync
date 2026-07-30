/*
 * EpochSync
 * Main Entry Point
 */

 #include "core/Application.h"
 #include <debug.h>
 #include "common/Logger.h"
 #include "common/Modules.h"
 #include "common/Version.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    init_scr();
    scr_clear();

    Logger_Initialize();

    Logger_Info(
        MODULE_APPLICATION,
        "Starting EpochSync %s.",
        EPOCHSYNC_VERSION_STRING);

    if (Application_Initialize() != EPOCHSYNC_SUCCESS)
    {
        Logger_Shutdown();
        return -1;
    }

    Application_Run();

    Application_Shutdown();

    Logger_Info(
        MODULE_APPLICATION,
        "Application exiting.");

    Logger_Shutdown();

    return 0;
}
/*
 * EpochSync
 * Main Entry Point
 */

 #include "core/Application.h"

 #include "common/Logger.h"
 #include "common/Modules.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    Logger_Info(
        MODULE_APPLICATION,
        "Starting EpochSync.");

    if (!Application_Initialize())
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
/*
 * EpochSync
 * Main Entry Point
 */

 #include "core/Application.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if (!Application_Initialize())
        return -1;

    Application_Run();

    Application_Shutdown();

    return 0;
}
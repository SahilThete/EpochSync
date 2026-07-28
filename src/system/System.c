/*
 * EpochSync
 * System Initialization
 *
 * Responsible for:
 *  - Initializing PS2SDK
 *  - Resetting the IOP
 *  - Applying SBV patches
 *  - Loading embedded IRX modules
 */

#include "System.h"
#include "../graphics/GraphicsManager.h"

/* PS2SDK */

#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <iopheap.h>
#include <iopcontrol.h>
#include <sbv_patches.h>

#include "../common/Logger.h"
#include "../common/Modules.h"

EpochSyncResult System_Initialize(void)
{
    Logger_Info(
        MODULE_SYSTEM,
        "Initializing system.");

    /* ---------- Initialize SIF ---------- */

    Logger_Info(
        MODULE_SYSTEM,
        "Initializing SIF.");

    SifInitRpc(0);
    SifLoadFileInit();
    SifInitIopHeap();


    /* ---------- Reset IOP ---------- */

    Logger_Info(
        MODULE_SYSTEM,
        "Resetting IOP.");

    while (!SifIopReset("", 0))
    {
    }

    while (!SifIopSync())
    {
    }

    /* ---------- Reinitialize ---------- */

    SifInitRpc(0);
    SifLoadFileInit();
    SifInitIopHeap();


    /* ---------- Apply SBV patches ---------- */

    Logger_Info(
        MODULE_SYSTEM,
        "Applying SBV patches.");

    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();

    /*
    * Future:
    * Load embedded IRX modules.
    */

    if (GraphicsManager_Initialize() != EPOCHSYNC_SUCCESS)
    {
        Logger_Error(
            MODULE_SYSTEM,
            "Graphics initialization failed.");

        return EPOCHSYNC_ERROR_UNKNOWN;
    }

    Logger_Info(
        MODULE_SYSTEM,
        "System initialization complete.");

    return EPOCHSYNC_SUCCESS;
}

void System_Shutdown(void)
{
    Logger_Info(
        MODULE_SYSTEM,
        "Shutting down system.");

    GraphicsManager_Shutdown();

    /*
     * Reserved.
     *
     * Future:
     * Unload services if required.
     */
}
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

/* PS2SDK */

#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <iopheap.h>
#include <iopcontrol.h>
#include <sbv_patches.h>

EpochSyncResult System_Initialize(void)
{
    /* ---------- Initialize SIF ---------- */

    SifInitRpc(0);
    SifLoadFileInit();
    SifInitIopHeap();

    /* ---------- Reset IOP ---------- */

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

    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();

    /*
     * Future:
     * Load embedded IRX modules.
     */

    return EPOCHSYNC_SUCCESS;
}

void System_Shutdown(void)
{
    /*
     * Reserved.
     *
     * Future:
     * Unload services if required.
     */
}
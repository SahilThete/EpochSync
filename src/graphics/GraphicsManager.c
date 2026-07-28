/*
 * EpochSync
 * Graphics Manager
 *
 * Responsible for:
 *  - Graphics initialization
 *  - Frame management
 *  - Screen clearing
 *  - Buffer swapping
 *  - VBlank synchronization
 */

#include "GraphicsManager.h"

#include "../common/Logger.h"
#include "../common/Modules.h"

EpochSyncResult GraphicsManager_Initialize(void)
{
    Logger_Info(
        MODULE_SYSTEM, 
        "Initializing graphics subsystem.");

    /*
     * gsKit initialization
     * will be added here.
     */

    return EPOCHSYNC_SUCCESS;
}

void GraphicsManager_Shutdown(void)
{
    Logger_Info(MODULE_SYSTEM,
        "Shutting down graphics subsystem.");

    /*
     * Reserved.
     */
}

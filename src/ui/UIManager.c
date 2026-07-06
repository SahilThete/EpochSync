/*
 * EpochSync
 * UI Manager
 *
 * Responsible for:
 *  - Screen management
 *  - Rendering
 *  - User interaction
 */

#include "UIManager.h"

static UIScreen g_CurrentScreen = UI_SCREEN_SPLASH;

EpochSyncResult UIManager_Initialize(void)
{
    g_CurrentScreen = UI_SCREEN_SPLASH;

    return EPOCHSYNC_SUCCESS;
}

void UIManager_Shutdown(void)
{
}

EpochSyncResult UIManager_SetScreen(UIScreen screen)
{
    g_CurrentScreen = screen;

    return EPOCHSYNC_SUCCESS;
}

void UIManager_Render(void)
{
    /*
     * Phase 2
     *
     * Render active screen.
     */
}

void UIManager_Update(void)
{
    /*
     * Phase 2
     *
     * Process controller input.
     */
}

UIScreen UIManager_GetScreen(void)
{
    return g_CurrentScreen;
}
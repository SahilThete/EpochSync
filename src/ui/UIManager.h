#ifndef EPOCHSYNC_UI_MANAGER_H
#define EPOCHSYNC_UI_MANAGER_H

#include "../common/Types.h"

/*----------------------------------------------------------
    UI Screens
----------------------------------------------------------*/

typedef enum
{
    UI_SCREEN_SPLASH,

    UI_SCREEN_MAIN,

    UI_SCREEN_PROGRESS,

    UI_SCREEN_CONFIRM,

    UI_SCREEN_ERROR,

    UI_SCREEN_EXIT

} UIScreen;

/*----------------------------------------------------------
    Lifecycle
----------------------------------------------------------*/

EpochSyncResult UIManager_Initialize(void);

void UIManager_Shutdown(void);

/*----------------------------------------------------------
    UI Operations
----------------------------------------------------------*/

EpochSyncResult UIManager_SetScreen(UIScreen screen);

void UIManager_Render(void);

void UIManager_Update(void);

/*----------------------------------------------------------
    State Queries
----------------------------------------------------------*/

UIScreen UIManager_GetScreen(void);

#endif /* EPOCHSYNC_UI_MANAGER_H */
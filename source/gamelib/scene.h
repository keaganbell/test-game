#pragma once
#include "defines.h"
#include "gamelib/ui.h"

typedef struct game game_t;

typedef enum scene_type {
    TITLE_SCENE,
    MENU_SCENE,
    PLAY_SCENE,

    MAX_SCENES
} scene_type_t;

typedef struct scene {
    b8 initialized;
    ui_context_t ui;
    
    b8   (*scene_init)(game_t *game);
    b8 (*scene_update)(game_t *game);
} scene_t;

b8 init_scenes(game_t *game);

#pragma once
#include "defines.h"
#include "gamelib/ui.h"

#include <raylib.h>

typedef enum state_mode
{
    TITLE,
    MENU,
    PLAYING,
    PAUSED,
    QUIT
} state_mode_t;

typedef struct game_state
{
    Camera3D camera;
    state_mode_t mode;
} game_state_t;

typedef struct game
{
    game_state_t *game_state;
    ui_context_t *ui_context;

    b8 (*init)(struct game *game);
    b8 (*update)(struct game *game);
    b8 (*shutdown)(struct game *game);
} game_t;

b8 update_title(game_t *game);
b8 update_menu(game_t *game);
b8 update_playing(game_t *game);

#pragma once
#include "defines.h"

#include <raylib.h>

typedef enum state_mode
{
    TITLE,
    MENU,
    PLAYING,
    PAUSED,
} state_mode_t;

typedef struct game_state
{
    Camera3D camera;
    state_mode_t mode;
} game_state_t;

typedef struct game
{
    game_state_t *game_state;

    b8 (*init)(struct game *game);
    b8 (*update)(struct game *game);
    b8 (*shutdown)(struct game *game);
} game_t;

b8 update_title(game_t *game);
b8 update_menu(game_t *game);
b8 update_playing(game_t *game);
b8 update_paused(game_t *game);

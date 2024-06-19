#pragma once
#include "defines.h"
#include "gamelib/scene.h"

#include <raylib.h>

typedef struct game_state {
    scene_t scenes[MAX_SCENES];
    scene_type_t current_scene;

    Camera3D camera;
} game_state_t;

typedef struct game {
    game_state_t *state;
    i32 width;
    i32 height;

    b8 (*init)(struct game *game);
    b8 (*update)(struct game *game);
    b8 (*shutdown)(struct game *game);
} game_t;

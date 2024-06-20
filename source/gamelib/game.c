#include "gamelib/game.h"
#include "gamelib/ui.h"
#include "coroutine.h"

#include <raylib.h>

#include <stdio.h>


b8 game_init(game_t *game) {
    if (!init_scenes(game)) {
        printf("ERROR: failed to initialize the game scenes.\n");
        return false;
    }
    if (!init_coroutines(game)) {
        printf("ERROR: failed to initialize the coroutines.\n");
        return false;
    }
    return true;
}

b8 game_update(game_t *game) {
    scene_t scene = game->state->scenes[game->state->current_scene];
    if (!scene.initialized) {
        scene.scene_init(game);
    }
    if (!scene.scene_update(game)) {
        return false;
    }
    return true;
}

b8 game_shutdown() {
    // proper shutdown sequence and serialization?
    // still want to save data throughout in case of crash
    return true;
}


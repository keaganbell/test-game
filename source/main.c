#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memset

#include <raylib.h>

#include "defines.h"
#include "loaddl.h"
#include "gamelib/coroutine.h"
#include "gamelib/game.h"
#include "gamelib/hotkeys.h"


b8 init_game(game_t *game) {
    if (!load_game_dl(game)) {
        printf("ERROR: failed to load game library.\n");
        return false;
    }
    game->state = malloc(sizeof(game_state_t));
    memset(game->state, 0, sizeof(game_state_t));
    game->width = 1200;
    game->height = 800;
    return true;
}

int main(void) {
    // start up the application ////////////////////////////////////////////////
    game_t game = {};
    if (!init_game(&game)) {
        printf("ERROR: failed to initialize the game application.\n");
        return 1;
    }

    // initialized the game ///////////////////////////////////////////////////
    if (!game.init(&game)) {
        printf("ERROR: game failed to initialize.\n");
        return 1;
    }


    // begin the game loop ///////////////////////////////////////////////////
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(game.width, game.height, "My Game Window");
//    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            game.width  = GetScreenWidth();
            game.height = GetScreenHeight();
        }
        // Hot reloading
        if (IsKeyReleased(KEY_HOTRELOAD)) {
            if (!hot_reload(&game)) {
                printf("ERROR: failed to hot reload game library.\n");
                break;
            }
        }
        if (!game.update(&game)) {
            printf("INFO: game is shutting down.\n");
            if (!game.shutdown(&game)) {
                printf("ERROR: game did not shutdown gracefully.\n");
            }
            break;
        }
        for (i32 i = 0; i < MAX_COROUTINES; ++i) {
            coroutine_t *coroutine = &game.state->coroutines[i];
            if (coroutine->update != 0 && !coroutine->done) {
                coroutine->update(&game);
            }
        }
    }
    CloseWindow();
    return 0;
}

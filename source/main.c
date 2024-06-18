#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memset

#include <raylib.h>

#include "defines.h"
#include "gamelib/game.h"
#include "gamelib/hotkeys.h"
#include "loaddl.h"


b8 init_app(game_t *game)
{
    if (!load_game_dl(game))
    {
        printf("ERROR: failed to load game library.\n");
        return false;
    }
    game->game_state = malloc(sizeof(game_state_t));
    memset(game->game_state, 0, sizeof(game_state_t));
    return true;
}

int main(void)
{
    // start up the application ////////////////////////////////////////////////
    game_t game = {};
    if (!init_app(&game))
    {
        printf("ERROR: failed to initialize the game application.\n");
        return 1;
    }

    // initialized the game ///////////////////////////////////////////////////
    if (!game.init(&game))
    {
        printf("ERROR: game failed to initialize.\n");
        return 1;
    }


    // begin the game loop ///////////////////////////////////////////////////
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(1200, 800, "My Game Window");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Hot reloading
        if (IsKeyReleased(KEY_HOTRELOAD))
        {
            if (!hot_reload(&game))
            {
                printf("ERROR: failed to hot reload game library.\n");
                break;
            }
        }
        if (!game.update(&game))
        {
            printf("INFO: game is shutting down.\n");
            if (!game.shutdown(&game))
            {
                printf("ERROR: game did not shutdown gracefully.\n");
            }
            break;
        }
    }
    CloseWindow();
    return 0;
}

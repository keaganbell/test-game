#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include "defines.h"
#include "gamelib/game.h"
#include "loaddl.h"


game_state_t *game_state;


b8 init_app(game_t *game)
{
    if (game == NULL)
    {
        printf("ERROR: game pointer was null.\n");
        return false;
    }

    if (game_state != NULL)
    {
        printf("ERROR: tried to initialize the game twice.\n");
        return false;
    }

    if (!load_game_dl(game))
    {
        printf("ERROR: failed to load game library.\n");
        return false;
    }
    game_state = malloc(sizeof(game_state_t));
    memset(game_state, 0, sizeof(game_state_t));
    game->game_state = game_state;
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
    InitWindow(1200, 800, "My Game Window");
    SetWindowPosition(0,0);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Hot reloading
        if (IsKeyReleased(KEY_F7))
        {
            if (!hot_reload(&game))
            {
                printf("ERROR: failed to hot reload game library.\n");
                break;
            }
        }
        game.update(&game);
    }
    CloseWindow();
    return 0;
}

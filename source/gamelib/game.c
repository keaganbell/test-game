#include "gamelib/game.h"
#include "gamelib/ui.h"
#include "gamelib/title.h"

#include <raylib.h>

#include <stdio.h>

b8 update_title(game_t *game)
{
    // do some cool intro
    game->game_state->mode = MENU;
    return true;
}

b8 update_menu(game_t *game)
{
    i32 screen_width = GetScreenWidth();
    i32 screen_height = GetScreenHeight();
    title_screen_t *title_screen = &game->game_state->title_screen;

    // create the title screen UI ////////////////////////////////////////////
    construct_title_screen(title_screen, screen_width, screen_height);
     
    // begin the rendering ///////////////////////////////////////////////////
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);

    // begin displaying UI elements
    DrawText("Ark of the Covenant", screen_width/2 - 230, screen_height/2 - 60, 48, LIGHTGRAY);
    if (button(&title_screen->ui_context, &title_screen->start_button))
    {
        game->game_state->mode = PLAYING;
    }
    if (button(&title_screen->ui_context, &title_screen->quit_button))
    {
        game->game_state->mode = QUIT;
    }
    EndDrawing();
    // end the rendering ///////////////////////////////////////////////////
    return true;
}

b8 update_playing(game_t *game)
{
    // begin the rendering /////////////////////////////////////////////////
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // begin camera 3d mode ////////////////////////////////////////////////
    BeginMode3D(game->game_state->camera);
    DrawGrid(10, 1.0f);
    EndMode3D();
    // end camera 3d mode //////////////////////////////////////////////////

    DrawFPS(10, 10);
    // end the rendering ///////////////////////////////////////////////////
    EndDrawing();
    return true;
}

b8 game_init(game_t *game)
{
    // define the camera
    game->game_state->camera.position = (Vector3){ 0.0f, 10.0f, 6.0f };   // Camera position
    game->game_state->camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    game->game_state->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    game->game_state->camera.fovy = 45.0f;                                // Camera field-of-view Y
    game->game_state->camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    printf("INFO: camera initialized successfully.\n");

    // explicitly set the state mode to the title screen
    game->game_state->mode = TITLE;
    return true;
}

b8 game_update(game_t *game)
{
    game_state_t *state = game->game_state;
 
    switch (state->mode)
    {
        case TITLE:
            if (!update_title(game))
            {
                printf("ERROR: failed to update the title screen.\n");
                return false;
            }
            break;
            
        case MENU:
            if (!update_menu(game))
            {
                printf("ERROR: failed to update the menu screen.\n");
                return false;
            }
            break;

        case PLAYING:
            if (!update_playing(game))
            {
                printf("ERROR: failed to update the gameplay.\n");
                return false;
            }
            break;

        case QUIT:
            return false;

        default:
            printf("ERROR: uknown game state mode.\n");
            return false;
    }
    return true;
}

b8 game_shutdown()
{
    // proper shutdown sequence and serialization?
    // still want to save data throughout in case of crash
    return true;
}


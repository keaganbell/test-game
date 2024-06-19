#include "gamelib/scene.h"
#include "gamelib/game.h"
#include "gamelib/ui.h"

b8 title_init(game_t *game) {
    scene_t *scene = &game->state->scenes[TITLE_SCENE];
    scene->initialized = true;
    return true;
}

b8 title_update(game_t *game) {
    game->state->current_scene = MENU_SCENE;
    return true;
}

b8 menu_init(game_t *game) {
    scene_t *scene = &game->state->scenes[MENU_SCENE];
    scene->initialized = true;
    return true;
}

b8 menu_update(game_t *game) {
    scene_t *scene = &game->state->scenes[MENU_SCENE];
    button_t start_button = {
        {1, 0, 0}, // uiid element {id, parent, child}
        {game->width/2 - 50, game->height/2 + 100, 100, 25}, // raylib Rectangle
        "Start Game", // button text
        LIGHTGRAY // button background color
    };

    button_t quit_button = {
        {2, 0, 0},
        {game->width/2 - 50, game->height/2 + 150, 100, 25},
        "Quit Game",
        LIGHTGRAY
    };
    BeginDrawing();
    ClearBackground(DARKGRAY);
    if (button(&scene->ui, &start_button)) {
        // begin transition event to play scene
        game->state->current_scene = PLAY_SCENE;
    }
    if (button(&scene->ui, &quit_button)) {
        return false;
    }
    EndDrawing();
    return true;
}

b8 play_init(game_t *game) {
    scene_t *scene = &game->state->scenes[PLAY_SCENE];
    scene->initialized = true;
    scene->camera.position = (Vector3){ 0.0f, 10.0f, 6.0f };   // Camera position
    scene->camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    scene->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    scene->camera.fovy = 45.0f;                                // Camera field-of-view Y
    scene->camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    printf("INFO: camera initialized successfully.\n");
    return true;
}

b8 play_update(game_t *game) {
    scene_t *scene = &game->state->scenes[PLAY_SCENE];
    // drawing /////////////////////////////////////////
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(scene->camera);
    DrawGrid(10, 1.0f);
    EndMode3D();

    EndDrawing();
    // drawing /////////////////////////////////////////
    return true;
}

b8 init_scenes(game_t *game) {
    for (i32 i = 0; i < MAX_SCENES; ++i) {
        if (game->state->scenes[i].initialized) {
            printf("ERROR: tried to initialize a scene twice.\n");
            return false;
        }
        switch (i) {
            case TITLE_SCENE:
                printf("INFO: hooking up title scene pfns\n");
                game->state->scenes[i].scene_init   = &title_init;
                game->state->scenes[i].scene_update = &title_update;
                break;

            case MENU_SCENE:
                printf("INFO: hooking up menu scene pfns\n");
                game->state->scenes[i].scene_init   = &menu_init;
                game->state->scenes[i].scene_update = &menu_update;
                break;

            case PLAY_SCENE:
                printf("INFO: hooking up play scene pfns\n");
                game->state->scenes[i].scene_init   = &play_init;
                game->state->scenes[i].scene_update = &play_update;
                break;

            default:
                printf("ERROR: unkown scene id.\n");
                return false;
        }
    }
    return true;
}

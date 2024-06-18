#include "gamelib/title.h"

#include <raylib.h>

b8 init_title_screen(title_screen_t *title_out)
{
    // initialize state pointers
    // and asset filepaths
    return true;
}

b8 construct_title_screen(title_screen_t *title_out, i32 screen_width, i32 screen_height)
{
    title_out->start_button = (button_t){
        {1, 0, 0}, // uiid element {id, parent, child}
        {screen_width/2 - 50, screen_height/2 + 100, 100, 25}, // raylib Rectangle
        "Start Game", // button text
        LIGHTGRAY // button background color
    };

    title_out->quit_button = (button_t){
        {2,0,0},
        {screen_width/2 - 50, screen_height/2 + 150, 100, 25},
        "Quit Game",
        LIGHTGRAY
    };
    return true;
}

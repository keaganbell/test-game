#pragma once

#include "defines.h"
#include "gamelib/ui.h"

typedef struct title
{
    char title[30];
    Rectangle rect;

    // path to image of title text art
} title_t;

typedef struct title_screen
{
    ui_context_t ui_context;
    title_t title;
    button_t start_button;
    button_t quit_button;

    // filepaths to background images and button images
} title_screen_t;

b8 init_title_screen(title_screen_t *title_out);
b8 construct_title_screen(title_screen_t *title_out, i32 screen_width, i32 screen_height);

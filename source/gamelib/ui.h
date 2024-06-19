#pragma once
#include "defines.h"

#include <raylib.h>

#include <stdio.h>

typedef struct uiid
{
    u64 id;
    u64 parent;
    u64 child;
} uiid_t;

typedef struct ui_context
{
    uiid_t active;
    uiid_t hot;
} ui_context_t;

typedef struct button
{
    uiid_t uiid;
    Rectangle rect;
    char *text;

    // color or texture
    Color color;
} button_t;

b8 button(ui_context_t *ui, button_t *button);

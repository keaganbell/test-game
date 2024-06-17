#include "gamelib/ui.h"

#include <stdio.h>

static inline b8 hovering_button(button_t *button)
{
    return (GetMouseX() >= button->rect.x &&
            GetMouseX() <= button->rect.x + button->rect.width &&
            GetMouseY() >= button->rect.y &&
            GetMouseY() <= button->rect.y + button->rect.height);
}

b8 button(ui_context_t *ui, button_t *button)
{
    if (!ui)
    {
        printf("ERROR: ui context was null!\n");
        return false;
    }

    if (!button)
    {
        printf("ERROR: button was null!\n");
        return false;
    }

    b8 result = false;
    // check if button is active ///////////////////////////////////////
    if (ui->active.id == button->uiid.id)
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && hovering_button(button))
        {
            if (ui->hot.id == button->uiid.id)
            {
                printf("INFO: button was clicked!\n");
                result = true;
            }
            ui->active.id = 0;
        }
        button->color = GREEN;
    }
    // check if button is hot //////////////////////////////////////////
    else if (ui->hot.id == button->uiid.id)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            printf("INFO: button is active!\n");
            ui->active.id = button->uiid.id;
        }
        button->color = RAYWHITE;
    }
    // set the hot button ///////////////////////////////////////////////
    if (hovering_button(button))
    {
        ui->hot.id = button->uiid.id;
    }

    // draw the button /////////////////////////////////////////////////
    DrawRectangleRec(button->rect, button->color);
    DrawText(button->text, button->rect.x, button->rect.y, 14, BLACK);
    return result;
}

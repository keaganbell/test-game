#include "uimanager.h"

void interpolate_color(Color *color_out, Color color_from, Color color_to, f32 dt)
{
    color_out->r = (color_to.r - color_from.r)*dt;
    color_out->g = (color_to.g - color_from.g)*dt;
    color_out->b = (color_to.b - color_from.b)*dt;
    color_out->a = (color_to.a - color_from.a)*dt;
}

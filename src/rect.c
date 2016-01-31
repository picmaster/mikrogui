/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "rect.h"
#include "framebuffer.h"

void mg_rect_draw(const mg_rect_t* const rect)
{
    int x, x_start, x_end;
    int y, y_start, y_end;

    if ((!rect)
        || (MG_WIDGET_TYPE_RECT != rect->widget.type))
        return;

    x_start = rect->widget.geometry.x;
    y_start = rect->widget.geometry.y;
    x_end = x_start + rect->widget.geometry.w;
    y_end = y_start + rect->widget.geometry.h;

    for (x = x_start; x < x_end; x++)
    {
        mg_framebuffer_draw_pixel(x, y_start, rect->color);
        mg_framebuffer_draw_pixel(x, y_end - 1, rect->color);
    }

    for (y = y_start; y < y_end; y++)
    {
        mg_framebuffer_draw_pixel(x_start, y, rect->color);
        mg_framebuffer_draw_pixel(x_end - 1, y, rect->color);
    }
}


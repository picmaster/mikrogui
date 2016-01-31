/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "progressbar.h"
#include "rect.h"
#include "framebuffer.h"

static void draw_fill(const mg_geometry_t* const g, mg_pixel_t color)
{
    uint16_t x, x_end;
    uint16_t y, y_end;

    if (!g)
        return;

    x_end = g->x + g->w;
    y_end = g->y + g->h;

    for (y = g->y; y < y_end; y++)
    {
        for (x = g->x; x < x_end; x++)
        {
            mg_framebuffer_draw_pixel(x, y, color);
        }
    }
}

void mg_progressbar_draw(const mg_progressbar_t* const pb)
{
    uint16_t fill_w;
    mg_rect_t r = {.widget = {.type = MG_WIDGET_TYPE_RECT}};
    mg_geometry_t g;

    if ((!pb)
        || (pb->widget.geometry.w < 3)
        || (pb->widget.geometry.h < 3))
        return;

    mg_widget_copy_geometry((mg_widget_t*)&r, (mg_widget_t*)pb);
    r.color = pb->border_color;
    mg_rect_draw(&r);

    fill_w = ((pb->widget.geometry.w - 2) * (pb->value - pb->min)) / (pb->max - pb->min);

    g.x = pb->widget.geometry.x + 1;
    g.y = pb->widget.geometry.y + 1;
    g.w = fill_w;
    g.h = pb->widget.geometry.h - 2;
    draw_fill(&g, pb->fg_color);

    g.x = pb->widget.geometry.x + 1 + fill_w;
    g.y = pb->widget.geometry.y + 1;
    g.w = pb->widget.geometry.w - 2 - fill_w;
    g.h = pb->widget.geometry.h - 2;
    draw_fill(&g, pb->bg_color);
}


/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mikrogui.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    int frames = 20 * 5, x, y;
    mg_rect_t r =
    {
        .widget =
        {
            .type = MG_WIDGET_TYPE_RECT,
            .geometry =
            {
                .w = 10,
                .h = 10
            }
        }
    };

    mg_init();

    while (frames--)
    {
        for (y = 0; y < MG_DISP_HEIGHT; y += r.widget.geometry.h + 1)
        {
            for (x = 0; x < MG_DISP_WIDTH; x += r.widget.geometry.w + 1)
            {
                r.widget.geometry.x = x;
                r.widget.geometry.y = y;
                r.color = x;
                mg_rect_draw(&r);
            }
        }

        mg_framebuffer_flush();
        usleep(50000);
    }

    return 0;
}


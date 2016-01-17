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

    mg_init();

    while (frames--)
    {
        for (y = 0; y < MG_DISP_HEIGHT; y++)
        {
            for (x = 0; x < MG_DISP_WIDTH; x++)
            {
                mg_framebuffer_draw_pixel(x, y, x);
            }
        }

        mg_framebuffer_flush();
        usleep(50000);
    }

    return 0;
}


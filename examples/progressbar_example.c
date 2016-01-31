/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mikrogui.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    int frames = 20 * 6, i = 0;
    mg_progressbar_t pb =
    {
        .widget =
        {
            .type = MG_WIDGET_TYPE_PROGRESSBAR,
            .geometry =
            {
                .x = 10,
                .y = 200,
                .w = 300,
                .h = 20
            }
        },
        .min = 0,
        .max = 100,
        .value = 50,

        .border_color = 0xFF,
        .fg_color = 0xFF,
        .bg_color = 0x80,
    };

    mg_init();

    while (frames--)
    {
        pb.value = i;
        mg_progressbar_draw(&pb);

        if (i < 100)
            i++;

        mg_framebuffer_flush();
        usleep(50000);
    }

    return 0;
}


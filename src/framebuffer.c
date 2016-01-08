/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "framebuffer.h"

extern fb_t fb;

void framebuffer_draw_pixel(const uint16_t x, const uint16_t y, const pixel_t c)
{
    if (x > fb.width || y > fb.height)
        return;

    switch (fb.pixel_format)
    {
        case PIXFMT_4BPP_MONO:
            break;

        case PIXFMT_8BPP_MONO:
        case PIXFMT_RGB332:
        default:
            *((pixel_t*)fb.mem + fb.width * y + x) = c;
            break;
    }
}

void framebuffer_clear(const pixel_t c)
{
    int x, y;

    for (y = 0; y < fb.height; y++)
        for (x = 0; x < fb.width; x++)
            framebuffer_draw_pixel(x, y, c);
}

void framebuffer_draw_line(const uint16_t x1, const uint16_t y1,
    const uint16_t x2, const uint16_t y2, const pixel_t c)
{
}

void framebuffer_draw_rect(const uint16_t x1, const uint16_t y1,
    const uint16_t x2, const uint16_t y2, const pixel_t c)
{
}

void framebuffer_flush(void)
{
    // Draw to the platform-specific backend
}


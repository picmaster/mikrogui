/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "framebuffer.h"

#include <string.h>

extern mg_fb_t fb;
extern void mg_platform_fb_flush(mg_fb_t* fb);

void mg_framebuffer_clear(void)
{
    memset(fb.mem, 0, fb.bytes);
}

void mg_framebuffer_draw_pixel(const uint16_t x, const uint16_t y, const mg_pixel_t c)
{
    mg_pixel_t* p = (mg_pixel_t*)fb.mem;

    if (x > fb.width || y > fb.height)
        return;

    switch (fb.pixel_format)
    {
        case PIXFMT_1BPP_MONO:
        case PIXFMT_2BPP_MONO:
        case PIXFMT_4BPP_MONO:
        case PIXFMT_8BPP_MONO:
        case PIXFMT_RGB332:
        default:
            p[fb.width * y + x] = c & MG_PIXEL_MASK;
            break;
    }
}

/*void mg_framebuffer_draw_line(const uint16_t x1, const uint16_t y1,
    const uint16_t x2, const uint16_t y2, const pixel_t c)
{
}*/

void mg_framebuffer_flush(void)
{
    mg_platform_fb_flush(&fb);
}


/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "framebuffer.h"
#include "platform.h"
#include <string.h>

extern mg_fb_t fb;

void mg_framebuffer_clear(void)
{
    memset(fb.mem, 0, fb.bytes);
}

void mg_framebuffer_draw_pixel(uint16_t x, uint16_t y, mg_pixel_t c)
{
    mg_pixel_t* p = (mg_pixel_t*)fb.mem;

    if ((x > fb.width) || (y > fb.height))
        return;

    switch (fb.pixel_format)
    {
        case PIXFMT_1BPP_MONO:
        case PIXFMT_2BPP_MONO:
        case PIXFMT_4BPP_MONO:
        case PIXFMT_8BPP_MONO:
        case PIXFMT_RGB332:
            p[fb.width * y + x] = c & MG_PIXEL_MASK;
            break;

        case PIXFMT_RGB565:
            break;

        case PIXFMT_RGB666:
        case PIXFMT_RGB888:
            break;
        default:
            break;
    }
}

void mg_framebuffer_flush(void)
{
    mg_platform_fb_flush(&fb);
}


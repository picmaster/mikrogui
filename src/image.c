/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "image.h"
#include "framebuffer.h"

// FIXME: Find better way to access the framebuffer
extern mg_fb_t fb;

// TODO: Look for possible performance optimizations
void mg_image_draw(mg_image_t* img)
{
    int x, x_end, x_offset;
    int y, y_end, y_offset;
    mg_pixel_t* p;

    if (!img || !img->pixmap.mem)
        return;

    // Clip the pixmap outside the widget & screen
    x_end = img->widget.geometry.x + img->pixmap.w;
    if (x_end > img->widget.geometry.w)
        x_end = img->widget.geometry.w;
    if (x_end > fb.width)
        x_end = fb.width;

    y_end = img->widget.geometry.y + img->pixmap.h;
    if (y_end > img->widget.geometry.h)
        y_end = img->widget.geometry.h;
    if (y_end > fb.height)
        y_end = fb.height;

    x_offset = img->widget.geometry.x;
    y_offset = img->widget.geometry.y;

    for (y = y_offset; y < y_end; y++)
    {
        for (x = x_offset; x < x_end; x++)
        {
            p = (mg_pixel_t*)img->pixmap.mem + (img->pixmap.w * (y - y_offset)) + (x - x_offset);

            // FIXME: Hardcoded
            // TODO: Check for pixmap's pixel format and convert properly the pixel
            mg_framebuffer_draw_pixel(x, y, *p >> 4);
        }
    }
}

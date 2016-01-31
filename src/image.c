/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "image.h"
#include "framebuffer.h"
#include <stdbool.h>

static bool mg_image_is_valid(const mg_image_t* const img)
{
    if ((!img)
        || (MG_WIDGET_TYPE_IMAGE != img->widget.type)
        || (!img->pixmap))
        return false;

    return true;
}

static bool mg_pixmap_is_valid(const mg_pixmap_t* const pixmap)
{
    if ((!pixmap)
        || (!pixmap->mem)
        || (pixmap->format <= PIXFMT_INVALID)
        || (pixmap->format >= PIXFMT_MAX))
        return false;

    return true;
}

uint32_t mg_pixmap_read_pixel(const mg_pixmap_t* const pixmap, uint16_t x,
    uint16_t y)
{
    uint32_t offset, pixel = 0;

    if ((!pixmap)
        || (!pixmap->mem)
        || (pixmap->format <= PIXFMT_INVALID)
        || (pixmap->format >= PIXFMT_MAX)
        || (x >= pixmap->w)
        || (y >= pixmap->h))
        return 0;

    switch (pixmap->format)
    {
        case PIXFMT_4BPP_MONO:
            offset = pixmap->w * y + x;
            pixel = ((uint8_t*)pixmap->mem)[offset >> 1];

            // FIXME: LSB/MSB pixel order is implicitly handled here, make sure
            // we handle it properly via the pixel format
            if (offset & 0x01)
                pixel = (pixel >> 4) & 0x0F;
            else pixel &= 0x0F;
            break;

        case PIXFMT_8BPP_MONO:
            offset = pixmap->w * y + x;
            pixel = ((uint8_t*)pixmap->mem)[offset];
            break;

        default:
            break;
    }

    return pixel;
}

// TODO: Look for possible performance optimizations
void mg_image_draw(const mg_image_t* const img)
{
    int x, x_end, x_offset;
    int y, y_end, y_offset;
    uint32_t pixel;

    if ((!mg_image_is_valid(img))
        || (!mg_pixmap_is_valid(img->pixmap)))
        return;

    // Clip the pixmap outside the widget
    x_end = img->widget.geometry.x + img->pixmap->w;
    if (x_end > img->widget.geometry.w)
        x_end = img->widget.geometry.w;

    y_end = img->widget.geometry.y + img->pixmap->h;
    if (y_end > img->widget.geometry.h)
        y_end = img->widget.geometry.h;

    x_offset = img->widget.geometry.x;
    y_offset = img->widget.geometry.y;

    for (y = y_offset; y < y_end; y++)
    {
        for (x = x_offset; x < x_end; x++)
        {
            pixel = mg_pixmap_read_pixel(&img->pixmap, x, y);

            // FIXME: Convert properly to the framebuffer's pixel format
            mg_framebuffer_draw_pixel(x, y, (pixel >> 4) & 0x0F);
        }
    }
}


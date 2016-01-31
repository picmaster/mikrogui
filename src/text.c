/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "text.h"
#include "framebuffer.h"

// Draw a single character with specified font
static void draw_char(const mg_font_t* const font, uint8_t c, uint16_t dst_x, uint16_t dst_y)
{
    int src_x = 0, src_y = 0, x, y;
    uint8_t color;

    if ((!font)
        || (!font->pixmap)
        || (!font->char_w)
        || (!font->char_h)
        || (!c))
        return;

    src_x = (c % 16) * font->char_w;
    src_y = (c / 16) * font->char_h;

    for (y = 0; y < font->char_h; y++)
    {
        for (x = 0; x < font->char_w; x++)
        {
            color = mg_pixmap_read_pixel(font->pixmap, src_x + x, src_y + y);
            mg_framebuffer_draw_pixel(dst_x + x, dst_y + y, color);
        }
    }
}

void mg_text_draw(const mg_text_t* const text)
{
    int i;

    if ((!text)
        || (!text->string.str)
        || (!text->string.len)
        || (!text->font))
        return;

    for (i = 0; i < text->string.len; i++)
    {
        draw_char(text->font, text->string.str[i],
            text->widget.geometry.x + (i * text->font->char_w),
            text->widget.geometry.y);
    }
}


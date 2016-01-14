/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "text.h"
#include "image.h"
#include "rect.h"
#include "resources.h"
#include "framebuffer.h"
#include <string.h>

// FIXME: Find better way to access the framebuffer
extern mg_fb_t fb;

#define ENABLE_DEBUG_OUTLINE 1

// FIXME: Font metrics are hard-coded, fix it
static void draw_char(mg_pixmap_t* sprite_map, uint8_t c, uint16_t dst_x,
    uint16_t dst_y)
{
    int x_offset = 0, y_offset = 0, x, y;
    uint8_t* p = NULL;
    uint8_t color;

    if (!sprite_map || !sprite_map->mem)
        return;

    p = (uint8_t*)sprite_map->mem;

    // Set offset relative to the sprite-map
    if (c >= 0x20 && c <= 0x39) // space..9
    {
        x_offset = (c - 0x20) * 8;
        y_offset = 0;
    }
    else if (c >= 0x41 && c <= 0x5A) // A..Z
    {
        x_offset = 0 + (c - 0x41) * 8;
        y_offset = 24;
    }
    else if (c >= 0x61 && c <= 0x7A) // a..z
    {
        x_offset = 0 + (c - 0x61) * 8;
        y_offset = 32;
    }
    else return;

    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            color = p[sprite_map->w * (y_offset + y) +  x_offset + x];
            mg_framebuffer_draw_pixel(dst_x + x, dst_y + y, color);
        }
    }
}

void mg_text_draw(const mg_text_t* text)
{
    int i;
    static mg_pixmap_t font = {&font8x8Bitmap, 256, 64};
#if ENABLE_DEBUG_OUTLINE
    mg_rect_t outline;
    //int x_pitch;
#endif

    if (!text || !text->str.len)
        return;

#if ENABLE_DEBUG_OUTLINE
    memset(&outline, 0, sizeof(outline));
    outline.widget.type = MG_WIDGET_TYPE_RECT;
    outline.widget.geometry.w = text->font.char_w;
    outline.widget.geometry.h = text->font.char_h;
    outline.widget.geometry.y = text->widget.geometry.y;
    outline.color = 7;
    //x_pitch = text->font.char_w + 1;
#endif

    for (i = 0; i < text->str.len; i++)
    {
#if ENABLE_DEBUG_OUTLINE
        //outline.widget.geometry.x = i * x_pitch;
        outline.widget.geometry.x = text->widget.geometry.x + i * 8;
        mg_rect_draw(&outline);
#endif
        draw_char(&font, text->str.str[i], text->widget.geometry.x + i * 8,
            text->widget.geometry.y);
    }
}

/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_IMAGE_H
#define MIKROGUI_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "widget.h"
//#include "framebuffer.h"
#include <stdint.h>

typedef struct
{
    void* mem;
    uint16_t w;
    uint16_t h;
    mg_pixel_format_t format;
} mg_pixmap_t;

typedef struct
{
    mg_widget_t widget;
    mg_pixmap_t pixmap;
} mg_image_t;

// Draw an image on the framebuffer
void mg_image_draw(mg_image_t* img);

// Read a single pixel from a pixmap
uint32_t mg_pixmap_read_pixel(const mg_pixmap_t* const pixmap,
    const uint16_t x, const uint16_t y);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_IMAGE_H


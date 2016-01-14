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

#include "widget.h"
#include <stdint.h>

typedef struct
{
    void* mem;
    uint16_t w;
    uint16_t h;
    // Pixel format, compression?
} mg_pixmap_t;

typedef struct
{
    mg_widget_t widget;
    mg_pixmap_t pixmap;
} mg_image_t;

void mg_image_draw(mg_image_t* img);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_IMAGE_H

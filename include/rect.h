/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_RECT_H
#define MIKROGUI_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "widget.h"

typedef struct
{
    mg_widget_t widget;
    mg_pixel_t color;
} mg_rect_t;

void mg_rect_draw(const mg_rect_t* rect);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_RECT_H

/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_PROGRESSBAR_H
#define MIKROGUI_PROGRESSBAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "widget.h"
#include "framebuffer_gen.h"
#include <stdint.h>

typedef struct
{
    mg_widget_t widget;

    uint16_t min;
    uint16_t max;
    uint16_t value;

    mg_pixel_t border_color;
    mg_pixel_t fg_color;
    mg_pixel_t bg_color;
} mg_progressbar_t;

void mg_progressbar_draw(const mg_progressbar_t* const pb);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_PROGRESSBAR_H


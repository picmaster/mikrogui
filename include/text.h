/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_TEXT_H
#define MIKROGUI_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "image.h"
#include "widget.h"

typedef struct
{
    const mg_pixmap_t* const pixmap;
    const uint16_t char_w;
    const uint16_t char_h;
} mg_font_t;

typedef struct
{
    mg_widget_t widget;
    mg_string_t string;
    const mg_font_t* const font;
} mg_text_t;

// Draw text
void mg_text_draw(const mg_text_t* const text);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_TEXT_H


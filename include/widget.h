/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_WIDGET_H
#define MIKROGUI_WIDGET_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    WIDGET_TYPE_INVALID = 0,
    WIDGET_TYPE_BUTTON,
    WIDGET_TYPE_TEXT,
    WIDGET_TYPE_PROGRESSBAR,
    WIDGET_TYPE_IMAGE,
    WIDGET_TYPE_MAX
} widget_type_t;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} geometry_t;

struct widget_s
{
    widget_s* parent;
    uint8_t id;
    uint8_t type;
    geometry_t geometry;
    widget_s* children;
};

typedef struct widget_s widget_t;

typedef struct
{
    uint8_t len;
    uint8_t* str;
} string_t;

typedef struct 
{
    widget_t base;
    string_t text;
    uint8_t font_id;
} button_t;

typedef struct
{
    widget_t widget;
    string_t text;
    uint8_t font_id;
} image_t;

typedef struct
{
    widget_t widget;
} form_t;

void widget_draw(widget_t* w);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_WIDGET_H


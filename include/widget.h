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

#include "common.h"
#include "input.h"
#include "framebuffer_gen.h" // TODO: Move mg_pixel_t type to another file to avoid this inclusion
#include <stdint.h>

typedef enum
{
    MG_WIDGET_TYPE_INVALID = 0,
    //MG_WIDGET_TYPE_BUTTON,
    MG_WIDGET_TYPE_FORM,
    MG_WIDGET_TYPE_IMAGE,
    //MG_WIDGET_TYPE_PROGRESSBAR,
    MG_WIDGET_TYPE_RECT,
    MG_WIDGET_TYPE_TEXT,
    MG_WIDGET_TYPE_MAX
} mg_widget_type_t;

typedef struct
{
    uint8_t type;
    mg_geometry_t geometry;
    void** children;
} mg_widget_t;

/*typedef struct 
{
    mg_widget_t base;
    mg_string_t text;
    uint8_t font_id;
} mg_button_t;
*/

typedef struct
{
    mg_widget_t widget;

    void (*enter)(void);
    void (*leave)(void);
    void (*handle_input)(mg_event_t e);
} mg_form_t;

void mg_widget_draw(const mg_widget_t* const widget);
mg_form_t* mg_widget_get_current_form(void);
void mg_widget_switch_form(const mg_form_t* const new_form);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_WIDGET_H


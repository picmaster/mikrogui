/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "widget.h"
#include "image.h"
#include "progressbar.h"
#include "rect.h"
#include "text.h"
#include "framebuffer.h"
#include <stdio.h>

static mg_form_t* current_form = NULL;

void mg_widget_copy_geometry(mg_widget_t* const dest, mg_widget_t* const src)
{
    if ((!dest) || (!src))
        return;

    dest->geometry = src->geometry;
}
// Nest-limiting won't work called from multithreaded code
void mg_widget_draw(const mg_widget_t* const widget)
{
    const int max_nest_level = 4;
    static int nest_level = 0;
    mg_widget_t** child = NULL;

    nest_level++;
    if ((!widget) || (nest_level >= max_nest_level))
        return;

    // Draw either the widget or its children
    switch (widget->type)
    {
        case MG_WIDGET_TYPE_FORM:
            for (child = widget->children; *child; child++)
                mg_widget_draw(*child);
            break;

        case MG_WIDGET_TYPE_IMAGE:
            mg_image_draw((mg_image_t*)widget);
            break;

        case MG_WIDGET_TYPE_PROGRESSBAR:
            mg_progressbar_draw((mg_progressbar_t*)widget);
            break;

        case MG_WIDGET_TYPE_RECT:
            mg_rect_draw((mg_rect_t*)widget);
            break;

        case MG_WIDGET_TYPE_TEXT:
            mg_text_draw((mg_text_t*)widget);
            break;

        default:
            break;
    }

    nest_level--;
}

// Return currently active form
mg_form_t* mg_widget_get_current_form(void)
{
    return current_form;
}

void mg_widget_switch_form(const mg_form_t* const new_form)
{
    if (!new_form)
        return;

    if (current_form && current_form->leave)
        current_form->leave();

    current_form = (mg_form_t*)new_form;

    if (current_form->enter)
        current_form->enter();

    mg_widget_draw((mg_widget_t*)current_form);
}


/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "widget.h"
#include "image.h"
#include "rect.h"
#include "framebuffer.h"
#include <stdio.h>

static mg_form_t* current_form = NULL;

// Nest-limiting won't work called from multithreaded code
void mg_widget_draw(mg_widget_t* widget)
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
            for (child = (mg_widget_t**)widget->children; *child; child++)
                mg_widget_draw(*child);
            break;

        case MG_WIDGET_TYPE_IMAGE:
            mg_image_draw((mg_image_t*)widget);
            break;

        case MG_WIDGET_TYPE_RECT:
        {
            mg_rect_draw((mg_rect_t*)widget);
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

void mg_widget_switch_form(mg_form_t* new_form)
{
    if (!new_form)
        return;

    if (current_form && current_form->leave)
        current_form->leave();

    current_form = new_form;

    if (current_form->enter)
        current_form->enter();

    mg_widget_draw((mg_widget_t*)current_form);
}

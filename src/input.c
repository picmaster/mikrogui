/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "input.h"
#include "widget.h"
#include "platform.h"
#include <stdio.h>

// Poll events from the platform
void mg_input_poll(void)
{
    mg_platform_input_poll();
}

// Deliver events to mikrogui
void mg_input_event(mg_event_t e)
{
    mg_form_t* form = NULL;

    form = mg_widget_get_current_form();
    if (form)
        form->handle_input(e);
}


/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_INPUT_H
#define MIKROGUI_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum
{
    EVT_TYPE_INVALID = 0,
    EVT_TYPE_BUTTON_PRESS,
    EVT_TYPE_BUTTON_RELEASE,
    EVT_TYPE_TOUCH_DOWN,
    EVT_TYPE_TOUCH_UP,
    EVT_TYPE_MAX
};

// FIXME: This should be auto-generated from the forms' specs
enum
{
    EVT_ID_INVALID = 0,
    EVT_ID_BUTTON1,
    EVT_ID_BUTTON2,
    EVT_ID_BUTTON3,
    EVT_ID_BUTTON4,
    EVT_ID_MAX
};

typedef struct
{
    uint16_t x;
    uint16_t y;
} mg_touch_data_t;

typedef struct
{
    uint8_t type;
    union
    {
        uint8_t button_id;
        mg_touch_data_t touch;
    } data;
} mg_event_t;

void mg_input_event(mg_event_t e);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_INPUT_H

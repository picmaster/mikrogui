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

enum
{
    EVENT_TYPE_INVALID = 0,
    EVENT_TYPE_BUTTON_PRESS,
    EVENT_TYPE_BUTTON_RELEASE,
    EVENT_TYPE_TOUCH_DOWN,
    EVENT_TYPE_TOUCH_UP,
};

// FIXME: This should be auto-generated from the forms' specs
enum
{
    EVENT_ID_INVALID = 0,
    EVENT_ID_BUTTON1,
    EVENT_ID_BUTTON2,
    EVENT_ID_BUTTON3,
    EVENT_ID_BUTTON4,
};

typedef struct
{
    uint16_t x;
    uint16_t y;
} touch_data_t;

typedef struct
{
    uint8_t type;
    union
    {
        uint8_t button_id;
        touch_data_t touch;
    } data;
} event_t;

void input_handle_event(event_t e);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_INPUT_H


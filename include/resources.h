/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// FIXME: Parts of this file should be automatically generated by the resource compiler!

#ifndef MIKROGUI_RESOURCES_H
#define MIKROGUI_RESOURCES_H

#ifdef __cplusplus
extern "C" {
#endif

// FIXME: Implement automatic resource generation
//#include "resources_gen.h"

#include <stdint.h>

/*typedef enum
{
    RES_ID_INVALID = 0,
    RES_ID_STRING1,
    RES_ID_STRING2,
    RES_ID_FONT_FIXED8,
    RES_ID_FONT_FIXED10,
    RES_ID_IMAGE_1,
    RES_ID_IMAGE_2,
    RES_ID_MAX
} resource_id_t;*/

typedef struct
{
    uint8_t* ptr;
    uint16_t len;
} resource_t;

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_RESOURCES_H


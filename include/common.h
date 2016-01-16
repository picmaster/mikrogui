/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_COMMON_H
#define MIKROGUI_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} mg_geometry_t;

typedef enum
{
    PIXFMT_INVALID = 0,
    PIXFMT_1BPP_MONO,
    PIXFMT_2BPP_MONO,
    PIXFMT_4BPP_MONO,
    PIXFMT_8BPP_MONO,
    PIXFMT_RGB332,
    PIXFMT_RGB565,
    PIXFMT_MAX
} mg_pixel_format_t;

typedef struct
{
    uint8_t len;
    uint8_t* str;
} mg_string_t;

typedef struct
{
    void* data;
    uint8_t char_w;
    uint8_t char_h;
} mg_font_t;

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_COMMON_H


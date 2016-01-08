/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_FRAMEBUFFER_H
#define MIKROGUI_FRAMEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "framebuffer_gen.h"

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
} pixel_format_t;

typedef struct
{
    void* mem;
    uint32_t bytes;
    uint32_t pixels;
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    uint8_t pixel_format;
} fb_t;

void framebuffer_clear(const pixel_t c);
void framebuffer_draw_pixel(const uint16_t x, const uint16_t y, const pixel_t c);
void framebuffer_draw_line(const uint16_t x1, const uint16_t y1,
    const uint16_t x2, const uint16_t y2, const pixel_t c);
void framebuffer_draw_rect(const uint16_t x1, const uint16_t y1,
    const uint16_t x2, const uint16_t y2, const pixel_t c);
void framebuffer_flush(void);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_FRAMEBUFFER_H


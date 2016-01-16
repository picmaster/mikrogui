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

#include "framebuffer_gen.h"
#include "common.h"
#include <stdint.h>

typedef struct
{
    void* mem;
    uint32_t bytes;
    uint32_t pixels;
    uint16_t width;
    uint16_t height;
    uint8_t pixel_format;
} mg_fb_t;

// Fill the framebuffer with black
void mg_framebuffer_clear(void);

// Draw single pixel
void mg_framebuffer_draw_pixel(const uint16_t x, const uint16_t y,
    const mg_pixel_t c);

// Write the framebuffer to the platform display
void mg_framebuffer_flush(void);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_FRAMEBUFFER_H


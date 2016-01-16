/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_PLATFORM_H
#define MIKROGUI_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "framebuffer.h"
#include "framebuffer_gen.h"

extern void mg_platform_init(const uint16_t disp_w, const uint16_t disp_h);
extern void mg_platform_run(void);
extern void mg_platform_fb_flush(mg_fb_t* fb);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_PLATFORM_H

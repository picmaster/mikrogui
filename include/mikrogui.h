/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIKROGUI_H
#define MIKROGUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "framebuffer.h"
#include "image.h"
#include "input.h"
#include "rect.h"
#include "resources.h"
#include "widget.h"

void mg_init(void);
void mg_run(void);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_H

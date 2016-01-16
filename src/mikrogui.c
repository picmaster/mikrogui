/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"

void mg_init(void)
{
    mg_platform_init(MG_DISP_WIDTH, MG_DISP_HEIGHT);
    mg_framebuffer_clear();
    mg_framebuffer_flush();
}

void mg_run(void)
{
    mg_platform_run();
}


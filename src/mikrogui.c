/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mikrogui.h"
#include "widget.h"
#include "framebuffer.h"

// FIXME: Fix these externs
extern int mg_platform_init(void);
extern void mg_platform_run(void);

// FIXME: Remove this extern
extern mg_fb_t fb;

void mg_init(void)
{
    mg_platform_init();
    mg_framebuffer_clear();
    mg_framebuffer_flush();
}

void mg_run(void)
{
    mg_platform_run();
}

// Example user application
/*int main(int argc, char** argv)
{
    mikrogui_init();
    mikrogui_run();

    return 0;
}*/

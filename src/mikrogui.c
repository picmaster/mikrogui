/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mikrogui.h"

// FIXME: Fix these externs
extern int mikrogui_platform_init(void);
extern void mikrogui_platform_run(void);

void mikrogui_init(void)
{
    mikrogui_platform_init();
    // Init menu system
}

void mikrogui_run(void)
{
    mikrogui_platform_run();
}

int main(int argc, char** argv)
{
    mikrogui_init();
    mikrogui_run();

    return 0;
}


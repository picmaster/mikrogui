/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SDL.h"

static SDL_Surface* screen = NULL;

// Return 0 on success, any other value on error
int mikrogui_platform_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(320, 240, 24, SDL_SWSURFACE);
    if (!screen)
    {
        printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void mikrogui_platform_run(void)
{
    SDL_Event evt;
    int running = 1;

    while (running)
    {
        // Handle pending events
        if (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    printf("evt.key.keysym.sym: %d, evt.key.type: %d\n", evt.key.keysym.sym, evt.key.type);
                    break;

                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }

        SDL_Delay(50);
    }

    SDL_Quit();
}


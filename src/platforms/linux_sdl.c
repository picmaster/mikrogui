/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "framebuffer.h"
#include "input.h"
#include "SDL.h"
#include <stdio.h>
#include <unistd.h>

static SDL_Surface* screen = NULL;
static uint32_t frames = 0;

const int zoom_min = 1;
const int zoom_max = 4;
int zoom = 1;

const int width = 64, height = 128;

// Return 0 on success, any other value on error
int mikrogui_platform_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(width * zoom, height * zoom, 24, SDL_SWSURFACE);
    if (!screen)
    {
        printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

void handle_zoom_event(int dir)
{
    int zoom_old = zoom;

    if (dir)
    {
        if (zoom < zoom_max)
            zoom++;
    }
    else
    {
        if (zoom > zoom_min)
            zoom--;
    }

    if (zoom_old != zoom)
    {
        screen = SDL_SetVideoMode(width * zoom, height * zoom, 24, SDL_SWSURFACE);
        if (!screen)
        {
            printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
            return;
        }
    }
}

void handle_events(SDL_KeyboardEvent ke)
{
    mg_event_t e;

    memset(&e, 0, sizeof(e));
    switch (ke.state)
    {
        case SDL_PRESSED:
            e.type = EVT_TYPE_BUTTON_PRESS;
            break;

        case SDL_RELEASED:
            e.type = EVT_TYPE_BUTTON_RELEASE;
            break;

        default:
            break;
    }

    switch (ke.keysym.sym)
    {
        // Special emulator key
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
            if (SDL_PRESSED == ke.state)
            handle_zoom_event(1);
            break;

        // Special emulator key
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
            if (SDL_PRESSED == ke.state)
            handle_zoom_event(0);
            break;

        case SDLK_1:
            e.data.button_id = EVT_ID_BUTTON1;
            break;

        case SDLK_2:
            e.data.button_id = EVT_ID_BUTTON2;
            break;

        case SDLK_3:
            e.data.button_id = EVT_ID_BUTTON3;
            break;

        case SDLK_4:
            e.data.button_id = EVT_ID_BUTTON4;
            break;

        default:
            break;
    }

    if (EVT_TYPE_INVALID != e.type && EVT_ID_INVALID != e.data.button_id)
        mg_input_event(e);
}

// FIXME: Invent better way to access the framebuffer
extern mg_fb_t fb;

void draw_pixel(SDL_Surface* s, int x, int y, mg_pixel_t c)
{
    int bpp = s->format->BytesPerPixel, xx, yy;
    Uint8* p;
    Uint32 c32 = 0;

    switch (fb.pixel_format)
    {
        case PIXFMT_1BPP_MONO:
            c32 = c ? 0xFFFFFF : 0;
            break;

        case PIXFMT_2BPP_MONO:
            c32 = (c << 22) | (c << 14) | (c << 6);
            break;

        case PIXFMT_4BPP_MONO:
            c32 = (c << 20) | (c << 12) | (c << 4);
            break;

        case PIXFMT_8BPP_MONO:
            c32 = (c << 16) | (c << 8) | c;
            break;

        default:
            break;
    }

    // Probably not the most efficient way to zoom a pixel, but it works
    for (yy = 0; yy < zoom; yy++)
    {
        for (xx = 0; xx < zoom; xx++)
        {
            switch (bpp)
            {
                // 24-bit color
                case 3:
                    p = (Uint8*)s->pixels + s->pitch * (y * zoom + yy) + (x * zoom + xx) * bpp;
                    if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
                    {
                        p[0] = c32 & 0xFF;
                        p[1] = (c32 >> 8) & 0xFF;
                        p[2] = (c32 >> 16) & 0xFF;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void mikrogui_platform_run(void)
{
    SDL_Event evt;
    int running = 1, x, y;
    char s[64];

    while (running)
    {
        snprintf(s, sizeof(s), "%dx%d, %dx, frames: %d", width, height, zoom, frames);
        SDL_WM_SetCaption(s, NULL);

        // Handle pending events
        if (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (SDLK_ESCAPE == evt.key.keysym.sym)
                        running = 0;

                    handle_events(evt.key);
                    break;

                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }

        // Update the screen
        SDL_LockSurface(screen);
        for (y = 0; y < fb.height; y++)
        {
            for (x = 0; x < fb.width; x++)
            {
                draw_pixel(screen, x, y, ((uint8_t*)fb.mem)[fb.width * y + x]);
            }
        }
        SDL_UnlockSurface(screen);
        SDL_UpdateRect(screen, 0, 0, width * zoom, height * zoom);

        SDL_Delay(50);
        frames++;
    }

    SDL_Quit();
}


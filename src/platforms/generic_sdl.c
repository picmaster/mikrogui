/*
 * Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "framebuffer.h"
#include "input.h"
#include "platform.h"
#include "SDL.h"
#include <stdio.h>
#include <unistd.h>

static SDL_Surface* screen = NULL;
static uint32_t frames = 0;

const int zoom_min = 1;
const int zoom_max = 4;
static int zoom = 1, width, height;

static mg_fb_t* vfb = NULL;

static void handle_zoom_event(int dir)
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

static void handle_events(SDL_KeyboardEvent ke)
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

void draw_pixel(SDL_Surface* s, int x, int y, mg_pixel_t c,
    mg_pixel_format_t pixfmt)
{
    int bpp = s->format->BytesPerPixel, xx, yy;
    Uint8* p;
    Uint32 c32 = 0;

    switch (pixfmt)
    {
        case PIXFMT_1BPP_MONO:
            c32 = (c & 0x1) ? 0xFFFFFF : 0;
            break;

        case PIXFMT_2BPP_MONO:
            c32 = ((c & 0x3) << 22) | ((c & 0x3) << 14) | ((c & 0x3) << 6);
            break;

        case PIXFMT_4BPP_MONO:
            c32 = (c << 20) | (c << 12) | (c << 4);
            break;

        case PIXFMT_8BPP_MONO:
            c32 = (c << 16) | (c << 8) | c;
            break;

        case PIXFMT_RGB332:
            c32 = ((c & 0xE) << 16) | ((c & 0x1C) << 11) | ((c & 0x3) << 6);
            break;

        case PIXFMT_RGB565:
            c32 = ((c & 0xF800) << 8) | ((c & 0x7E0) << 5) | ((c & 0x1F) << 3);
            break;

        case PIXFMT_RGB666:
            c32 = ((c & 0x3F000) << 6) | ((c & 0xFC0) << 4) | ((c & 0x3F) << 2);
            break;

        case PIXFMT_RGB888:
            c32 = c & 0xFFFFFF;
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

// Return 0 on success, any other value on error
int mg_platform_init(const uint16_t disp_w, const uint16_t disp_h)
{
    width = disp_w;
    height = disp_h;

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

void mg_platform_run(void)
{
    SDL_Event evt;
    int running = 1;
    //int x, y;
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

        mg_platform_fb_flush(vfb);

        SDL_Delay(50);
        frames++;
    }

    SDL_Quit();
}

// Update the screen
void mg_platform_fb_flush(mg_fb_t* fb)
{
    int x, y;
    uint8_t* p;

    if (!fb)
        return;

    vfb = fb;

    SDL_LockSurface(screen);
    for (y = 0; y < vfb->height; y++)
    {
        for (x = 0; x < vfb->width; x++)
        {
            p = ((uint8_t*)vfb->mem) + vfb->width * y + x;
            draw_pixel(screen, x, y, *p, vfb->pixel_format);
        }
    }
    SDL_UnlockSurface(screen);
    SDL_UpdateRect(screen, 0, 0, width * zoom, height * zoom);
}

void mg_platform_input_poll()
{
    SDL_Event evt;

    // Handle pending events
    if (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                /*if (SDLK_ESCAPE == evt.key.keysym.sym)
                    running = 0;*/

                handle_events(evt.key);
                break;

            case SDL_QUIT:
                //running = 0;
                break;
        }
    }
}

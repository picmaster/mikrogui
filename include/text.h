#ifndef MIKROGUI_TEXT_H
#define MIKROGUI_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "image.h"
#include "widget.h"

typedef struct
{
    mg_pixmap_t* pixmap;
    uint16_t char_w;
    uint16_t char_h;
} mg_font_t;

typedef struct
{
    mg_widget_t widget;
    mg_string_t string;
    mg_font_t* font;
} mg_text_t;

// Draw text
void mg_text_draw(const mg_text_t* text);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_TEXT_H


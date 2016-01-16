#ifndef MIKROGUI_TEXT_H
#define MIKROGUI_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "widget.h"

typedef struct
{
    mg_widget_t widget;
    mg_string_t string;
    mg_font_t font;
} mg_text_t;

void mg_text_draw(const mg_text_t* text);

#ifdef __cplusplus
}
#endif

#endif // MIKROGUI_TEXT_H


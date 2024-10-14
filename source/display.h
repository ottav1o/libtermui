#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdbool.h>

#include "pixels.h"
#include "cursor.h"
#include "canvas.h"

typedef struct {
    const char *display_name;
    unsigned short height, width;
    bool dynamic;
    Pixel *display_pixels;
    size_t pixels_count;
    Cursor cursor;
    Canvas main_canvas;
} Display;

Display * __tui_create_display(unsigned short height, unsigned short width, const char *name);
void __tui_destroy_display(Display *display);

#endif // __DISPLAY_H__
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "pixels.h"

#include <stdio.h>

typedef struct _canvas {
    struct _canvas *parent;
    Pixel **pixels;
    size_t pixels_count;
    struct _canvas **childs;
    size_t childs_count;
} Canvas;

Canvas * __tui_create_canvas(Pixel **pixels, size_t pcount);
void __tui_destroy_canvas(Canvas *canvas);

#endif // __CANVAS_H__

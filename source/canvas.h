#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "pixels.h"

typedef struct _canvas {
    Pixel **pixels;
    unsigned short pixels_count;
    struct _canvas **childs;
    unsigned int childs_count;
} Canvas;

Canvas * __tui_create_canvas(Pixel **pixels, unsigned short pcount);
void __tui_destroy_canvas(Canvas *canvas);

#endif // __CANVAS_H__

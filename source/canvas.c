#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Canvas * __tui_create_canvas(Pixel **pixels, unsigned short pcount) {
    Canvas *canvas = malloc(sizeof(Canvas));
    if (canvas == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for canvas.\n");
        return NULL;
    }

    canvas->pixels = pixels;
    canvas->pixels_count = pcount;
    canvas->childs = NULL;
    canvas->childs_count = 0;

    return canvas;
}

void __tui_destroy_canvas(Canvas *canvas) {
    assert(canvas && "*canvas is NULL");

    if (canvas->pixels) {
        free(canvas->pixels);
        canvas->pixels = NULL;
    }

    free(canvas);
    canvas = NULL;
}

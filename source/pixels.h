#ifndef __PIXELS_H__
#define __PIXELS_H__

#include <stdbool.h>

typedef enum {
    TUI_CANVAS_PIXEL_READ,
    TUI_CANVAS_PIXEL_WRITE,
} TUI_PIXEL_PERMISSIONS;

typedef struct {
    char c;
    bool locked;
    TUI_PIXEL_PERMISSIONS perm;
} Pixel;

#endif // __PIXELS_H__

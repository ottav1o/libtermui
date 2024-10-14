#ifndef __RENDERER_H___
#define __RENDERER_H___

#include <stdio.h>
#include "display.h"

int __tui_renderer_write(Display *display, FILE *stream);
void __tui_renderer_clear(FILE *stream);

#endif // __RENDERER_H___

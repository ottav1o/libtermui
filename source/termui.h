#ifndef __TERM_UI_H__
#define __TERM_UI_H__

#include "display.h"
#include "cursor.h"
#include "pixels.h"
#include "renderer.h"
#include "canvas.h"

#include <stdio.h>

#define TERMUI_AUTODETECT 0
#define DEFAULT_RENDERER stdout

#define TERMUI_LIB_VERSION "0.5.0-dev-release"

struct _tracker {
    Display **all_displays;
    Canvas **all_canvas;
    size_t display_count;
    size_t canvas_count;
};

int termui_init(void);
void termui_close(void);
const char * termui_version(void);

Display * termui_create_display(unsigned short rows, unsigned short cols, const char *name);
void termui_destroy_display(Display *display);

Canvas * termui_create_canvas(Pixel **pixels, size_t pixels_count);
void * termui_destroy_canvas(Canvas *canvas);

int termui_renderer_present(Display *display);
void termui_renderer_clear(void);

void termui_move_cursor(Display *display, unsigned short row, unsigned short col);
void termui_reset_cursor(Display *display);

size_t termui_insert_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *text);
size_t termui_insertf_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *fmt, ...);
size_t termui_erase(Canvas *canvas, Pixel **pixels, size_t pixels_count);

size_t termui_insert_textl(Canvas *canvas, unsigned short start, const char *text);
size_t termui_insertf_textl(Canvas *canvas, unsigned short start, const char *fmt, ...);
size_t termui_erasel(Canvas *canvas, unsigned short start, unsigned short end);

#endif // __TERM_UI_H__

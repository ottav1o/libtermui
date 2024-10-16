/*
 *    BSD 3-Clause License
 *
 *    Copyright (c) 2024, ottav1o
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

int termui_canvas_add_child(Canvas *parent, Canvas *child);
int termui_canvas_remove_child(Canvas *parent, size_t index);

#endif // __TERM_UI_H__

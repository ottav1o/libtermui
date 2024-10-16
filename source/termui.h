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

#define TERMUI_LIB_VERSION "0.6.0-dev-release"

/* Tracks all displays and canvas created. */
struct _tracker {
    Display **all_displays;
    Canvas **all_canvas;
    size_t display_count;
    size_t canvas_count;
};

/* Init function, get the terminal size and intialize the tracker */
int termui_init(void);
/* Close function, destroy all created canvas and displays and close */
void termui_close(void);
const char * termui_version(void);

/* Create a new display and add it to the tracker. Wrapper for `__tui_create_display()` */
Display * termui_create_display(unsigned short rows, unsigned short cols, const char *name);
/* Delete `display` and removes it from the tracker. Wrapper for `__tui_destroy_display()` */
void termui_destroy_display(Display *display);

/* Create a new canvas with `**pixels` and `pixels_count` size and add it to the tracker. beware that if you provide a different pixel count probaly this will gonna crash. Wrapper for `__tui_create_canvas()` */
Canvas * termui_create_canvas(Pixel **pixels, size_t pixels_count);
/* Destroy `*canvas`, remove it from the tracker and deallocate memory for `**pixels`. Wrapper for `__tui_destroy_canvas()` */
void * termui_destroy_canvas(Canvas *canvas);

/* Render the `display->pixels` line by line to the STDOUT. Wrapper to `__tui_renderer_write()` */
int termui_renderer_present(Display *display);
/* Clear everything on the screen. Note: This function should not be used in the main loop before or after `termui_renderer_present()`. `termui_renderer_present()` already overwrite changes int the STDOUT.*/
void termui_renderer_clear(void);

/* Move `display->cursor` to row `row` and col `col`. Changes only apply on the next `__tui_renderer_write()` call */
void termui_move_cursor(Display *display, unsigned short row, unsigned short col);
/* Reset `display->cursor` to row 0 and col 0 "home". Changes only apply on the next `__tui_renderer_write()` call */
void termui_reset_cursor(Display *display);

/* Insert text `*text` to pixels `**pixels` array */
size_t termui_insert_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *text);
/* Insert formatted text `*text` to pixels `**pixels` array */
size_t termui_insertf_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *fmt, ...);
/* Erase `pixels_count` pixels */
size_t termui_erase(Canvas *canvas, Pixel **pixels, size_t pixels_count);

/* Insert a continuous line of text `*text` to pixels `**pixels` array */
size_t termui_insert_textl(Canvas *canvas, unsigned short start, const char *text);
/* Insert a continuous line of formatted text `*text` to pixels `**pixels` array */
size_t termui_insertf_textl(Canvas *canvas, unsigned short start, const char *fmt, ...);
/* Erase a continuous line of `pixels_count` pixels */
size_t termui_erasel(Canvas *canvas, unsigned short start, unsigned short end);

#endif // __TERM_UI_H__

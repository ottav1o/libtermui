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

#define _XOPEN_SOURCE 500

#include "termui.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

static struct winsize terminal_info;
static struct _tracker tracker;
static bool __is_termui_initialized = false;

int termui_init(void) {
    if (__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is alreaady initialized.\n");
        return -1;
    }

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal_info);
    tracker.all_displays = NULL;
    tracker.all_canvas = NULL;
    tracker.display_count = 0;
    tracker.canvas_count = 0;

    __is_termui_initialized = true;

    return 0;
}

void termui_close(void) {
    if (!__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is not initalized.\n");
        assert(false && "Assertion Message: Is termui initialized?");
    }

    __is_termui_initialized = false;

    if (tracker.all_displays != NULL) {
        for (size_t i = 0; i < tracker.display_count; i++) {
            if (tracker.all_displays[i]) {
                __tui_destroy_display(tracker.all_displays[i]);
                tracker.all_displays[i] = NULL;
            }
        }

        free(tracker.all_displays);
        tracker.all_displays = NULL;
    }

    if (tracker.all_canvas != NULL) {
        for (size_t i = 0; i < tracker.canvas_count; i++) {
            if (tracker.all_canvas[i]) {
                __tui_destroy_canvas(tracker.all_canvas[i]);
                tracker.all_canvas[i] = NULL;
            }
        }

        free(tracker.all_canvas);
        tracker.all_canvas = NULL;
    }

    fprintf(DEFAULT_RENDERER, "\033[2J");
    fprintf(DEFAULT_RENDERER, "\033[0;0H");
}

const char * termui_version(void) {
    return TERMUI_LIB_VERSION;
}

Display * termui_create_display(unsigned short rows, unsigned short cols, const char *name) {
    if (!__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is not initalized.\n");
        assert(false && "Assertion Message: Is termui initialized?");
    }

    if (rows == TERMUI_AUTODETECT) {
        rows = terminal_info.ws_row;
    }
    
    if (cols == TERMUI_AUTODETECT) {
        cols = terminal_info.ws_col;
    }
    
    Display *display = __tui_create_display(rows, cols, name);
    if (display == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate necesary memory for display.\n");
        return NULL;
    }

    if (tracker.display_count == 0 || tracker.all_displays == NULL) {
        tracker.all_displays = malloc(sizeof(Display *));
        if (tracker.all_displays == NULL) {
            fprintf(stderr, "ERROR: Cannot allocate necessary memory for displays pointer.\n");

            return NULL;
        }

        tracker.display_count = 1;
    }

    tracker.all_displays[tracker.display_count - 1] = display;
    tracker.display_count++;

    tracker.all_displays = realloc(tracker.all_displays, sizeof(Display *) * tracker.display_count);
    if (tracker.all_displays == NULL) {
        fprintf(stderr, "ERROR: Cannot add display to display tracker: Failed to allocate memory for display pointer.\n");

        __tui_destroy_display(display);
        display = NULL;

        tracker.display_count = 0;

        return NULL;
    }

    return display;
}

void termui_destroy_display(Display *display) {
    if (!__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is not initalized.\n");
        assert(false && "Assertion Message: Is termui initialized?");
    }

    /* comment by: ottav1o | m10/d12/y24 - 23:44 UTC +0 */
    /* wasting performance (and memory), but im too lazy to implement a better way to do it */
    /* TODO: Refactor everything */
    for (size_t i = 0; i < tracker.display_count; i++) {
        if (display == tracker.all_displays[i]) {
            __tui_destroy_display(tracker.all_displays[i]);
            tracker.all_displays[i] = NULL;
        }
    }
}

Canvas * termui_create_canvas(Pixel **pixels, size_t pixels_count) {
    if (!__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is not initalized.\n");
        assert(false && "Assertion Message: Is termui initialized?");
    }

    Canvas *canvas = __tui_create_canvas(pixels, pixels_count);
    if (canvas == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate necessary memory for canvas.\n");
        
        return NULL;
    }

    if (tracker.all_canvas == NULL || tracker.canvas_count == 0) {
        tracker.all_canvas = malloc(sizeof(Canvas *));
        if (tracker.all_canvas == NULL) {
            fprintf(stderr, "ERROR: Cannot allocate necessary memory for tracker canvas pointer.\nn");

            free(canvas);
            canvas == NULL;

            return NULL;
        }
        
        tracker.canvas_count = 1;
    }


    tracker.all_canvas[tracker.canvas_count - 1] = canvas;
    tracker.canvas_count++;

    tracker.all_canvas = realloc(tracker.all_canvas, sizeof(Canvas *) * tracker.canvas_count);
    if (tracker.all_canvas == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate necessary memory for tracker canvas pointer.\n");

        free(canvas);
        canvas = NULL;
        tracker.canvas_count = 0;

        return NULL;
    }

    return canvas;
}

void * termui_destroy_canvas(Canvas *canvas) {
    if (!__is_termui_initialized) {
        fprintf(stderr, "ERROR: termui is not initalized.\n");
        assert(false && "Assertion Message: Is termui initialized?");
    }

    // wasting memory
    // FIXME: not waste memory
    for (size_t i = 0; i < tracker.canvas_count; i++) {
        if (canvas == tracker.all_canvas[i]) {
            __tui_destroy_canvas(tracker.all_canvas[i]);
            tracker.all_canvas[i] = NULL;
        }
    }

    canvas = NULL;
}

int termui_renderer_present(Display *display) {
    assert(display && "Assertion Message: Display is NULL.");
    
    termui_reset_cursor(display);
    __tui_renderer_write(display, DEFAULT_RENDERER);

    return 0;
}

void termui_renderer_clear(void) {
    __tui_renderer_clear(DEFAULT_RENDERER);
}

void termui_move_cursor(Display *display, unsigned short row, unsigned short col) {
    assert(display && "Assertion Message: *display is NULL");
    __tui_cursor_move(row, col, &display->cursor);
}

void termui_reset_cursor(Display *display) {
    assert(display && "Assertion Message: *display is NULL");
    __tui_cursor_move(0, 0, &display->cursor);
}

size_t termui_insert_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *text) {
    assert(canvas && "Assertion Message: *canvas is NULL");
    assert(pixels && "Assertion Message: **pixels is NULL");
    assert(text && "Assertion Message: *text is NULL");

    size_t len = strlen(text);
    for (size_t i = 0; i < pixels_count && i < len; i++)
        pixels[i]->c = text[i];

    return len;
}

size_t termui_insertf_text(Canvas *canvas, Pixel **pixels, size_t pixels_count, const char *fmt, ...) {
    assert(canvas && "Assertion Message: *canvas is NULL");
    assert(pixels && "Assertion Message: **pixels is NULL");
    assert(fmt && "Assertion Message: *fmt is NULL");

    va_list args;
    va_start(args, fmt);

    char *text;
    char buffer[256];
    size_t lenght;

    lenght = vsnprintf(buffer, sizeof(buffer), fmt, args);

    if (lenght < sizeof(buffer)) {
        text = strdup(buffer);
    
    } else {
        text = malloc(sizeof(char) * (lenght + 1));
    }

    if (text == NULL) {
        return -1;
    }

    if (lenght >= sizeof(buffer)) {
        lenght = vsnprintf(text, lenght + 1, fmt, args);
    }

    va_end(args);

    for (size_t i = 0; i < pixels_count && i < strlen(text); i++)
        pixels[i]->c = text[i];

    free(text);
    text = NULL;

    return lenght;
}

size_t termui_erase(Canvas *canvas, Pixel **pixels, size_t pixels_count) {
    assert(canvas && "Assertion Message: *canvas is NULL");
    assert(pixels && "Assertion Message: **pixels is NULL");

    for (size_t i = 0; i < pixels_count; i++)
        pixels[i]->c = ' ';

    return pixels_count;
}

size_t termui_insert_textl(Canvas *canvas, unsigned short start, const char *text) {
    size_t len = strlen(text);
    if (start + len > canvas->pixels_count) {
        fprintf(stderr, "ERROR: Cannot insert text to canvas: Index out of range.\n");
        return -1;
    }

    for (size_t i = 0; i < len; i++)
        canvas->pixels[start+i]->c = text[i];

    return len;
}

size_t termui_insertf_textl(Canvas *canvas, unsigned short start, const char *fmt, ...) {
    assert(canvas && "Assertion Message: *canvas is NULL");
    assert(fmt && "Assertion Message: *fmt is NULL");

    va_list args;
    va_start(args, fmt);

    char *text;
    char buffer[256];
    size_t lenght;

    lenght = vsnprintf(buffer, sizeof(buffer), fmt, args);

    if (lenght < sizeof(buffer)) {
        text = strdup(buffer);
    
    } else {
        text = malloc(sizeof(char) * (lenght + 1));
    }

    if (text == NULL) {
        return -1;
    }

    if (lenght >= sizeof(buffer)) {
        lenght = vsnprintf(text, lenght + 1, fmt, args);
    }

    va_end(args);

    if (start + lenght > canvas->pixels_count) {
        fprintf(stderr, "ERROR: Cannot insert text to canvas: Index out of range.\n");
        
        free(text);
        text = NULL;

        return -1;
    }

    for (size_t i = 0; i < lenght && i < strlen(text); i++)
        canvas->pixels[start+i]->c = text[i];

    free(text);
    text = NULL;

    return lenght;
}

size_t termui_erasel(Canvas *canvas, unsigned short start, unsigned short end) {
    if (end > canvas->pixels_count) {
        fprintf(stderr, "ERROR: Cannot insert text to canvas: Index out of range.\n");
        
        return -1;
    }
    
    size_t len = end - start;

    for (size_t i = 0; i < len; i++)
        canvas->pixels[start+i]->c = ' ';

    return len;
}

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

#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pixels.h"

Display * __tui_create_display(unsigned short height, unsigned short width, const char *name) {
    Display *display = malloc(sizeof(Display));
    if (display == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate Display.\n");
        return NULL;
    }

    display->height = height;
    display->width  = width;
    display->pixels_count = display->height * display->width;

    Pixel *pixel_array = malloc(sizeof(Pixel) * display->pixels_count);
    if (pixel_array == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate display pixel array. Aborting display creation.\n");
        free(display);
        display = NULL;

        return NULL;
    }

    display->display_pixels = pixel_array;

    display->dynamic = false;
    display->display_name = name;

    display->main_canvas.pixels = malloc(sizeof(Pixel *) * display->pixels_count);
    if (display->main_canvas.pixels == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for the main canvas pixels pointer Aborting display creation.\n");

        free(display->display_pixels);
        display->display_pixels = NULL;

        free(display);
        display = NULL;

        return NULL;
    }

    display->main_canvas.childs = NULL;
    display->main_canvas.childs_count = 0;

    for (size_t i = 0; i < display->pixels_count; i++) {
        display->main_canvas.pixels[i] = &display->display_pixels[i];
        display->main_canvas.pixels[i]->c = ' ';
    }
    display->main_canvas.pixels_count = display->pixels_count;
    
    display->main_canvas.parent = NULL;

    __tui_cursor_move(0, 0, &display->cursor);

    return display;
}

void __tui_destroy_display(Display *display) {
    assert(display && "Display is NULL.");


    if (display->display_pixels) {
        free(display->display_pixels);
        display->display_pixels = NULL;
    }

    if (display->main_canvas.pixels) {
        free(display->main_canvas.pixels);
        display->main_canvas.pixels = NULL;
    }

    // TODO: recursively destroy all canvas childs

    free(display);
    display = NULL;
}

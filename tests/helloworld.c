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

#include <stdio.h>
#include <stdlib.h>

#include "../source/termui.h"

int main(void) {
    termui_init();

    Display *display = termui_create_display(TERMUI_AUTODETECT, TERMUI_AUTODETECT, "Init Screen");
    if (display == NULL) {
        perror("Hey whats up");
        return 1;
    }

    Pixel **pixels = malloc(sizeof(Pixel *) * 13);
    for (size_t i = display->main_canvas.pixels_count - 13, j = 0; i < display->main_canvas.pixels_count - 1; i++, j++)
        pixels[j] = display->main_canvas.pixels[i];

    // termui_insert_text(&display->main_canvas, pixels, 12, "Hello World");

    Canvas *canv = termui_create_canvas(pixels, 13);
    termui_canvas_add_child(&display->main_canvas, canv);

    termui_insert_textl(canv, 0, "Hello World!");
    puts("Hello");
    termui_insertf_textl(&display->main_canvas, 13, "This is a test: Terminal size: Rows: %d, Width: %d", display->height, display->width);
    termui_insert_textl(&display->main_canvas, 1*display->width, termui_version());

    termui_canvas_remove_child(&display->main_canvas, display->main_canvas.childs_count - 1);

    termui_destroy_canvas(canv);
    termui_renderer_present(display);

    getchar();  

    // termui_renderer_clear();

    puts(display->display_name);
    termui_close();

    return 0;
}
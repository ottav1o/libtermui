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
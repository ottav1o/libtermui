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

    // Pixel **pixels = malloc(sizeof(Pixel *) * 12);
    // for (size_t i = 0; i < 12; i++) {
    //     pixels[i] = display->main_canvas.pixels[(i*display->width) + i * 4];
    //     printf("%d\n", (i*display->width) + i * 4);
    // }

    // termui_insert_text(&display->main_canvas, pixels, 12, "Hello World");

    termui_insert_textl(&display->main_canvas, 0, "Hello World!");
    termui_insertf_textl(&display->main_canvas, 13, "This is a test: Terminal size: Rows: %d, Width: %d", display->height, display->width);
    termui_insert_textl(&display->main_canvas, 1*display->width, termui_version());

    termui_renderer_present(display);

    getchar();  

    // termui_renderer_clear();
    puts(display->display_name);
    termui_close();

    return 0;
}
#include "renderer.h"

int __tui_renderer_write(Display *display, FILE *stream) {
    fprintf(stream, "\033[%d;%dH", display->cursor.row, display->cursor.col);

    char text[display->pixels_count];

    for (size_t i = 0; i < display->pixels_count; i++)
        text[i] = display->display_pixels[i].c;
    
    for (unsigned int i = 0; i < display->height; i++) {
        fwrite(&text[i*display->width], sizeof(char) * display->width, 1, stream);
        if (i != display->height - 1)
            fputc('\n', stream);
    }

    return 0;
}

void __tui_renderer_clear(FILE *stream) {
    fprintf(stream, "\033[2J");
}

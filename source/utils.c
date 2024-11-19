#include "utils.h"

#include "termui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

Pixel ** termui_utils_gen_pixels(Canvas *from, unsigned short start, unsigned short end, int intervals)
{
    if (end >= from->pixels_count)
    {
        fprintf(stderr, "ERROR: Cannot generate pixels from %d to %d: Index out of range.\n", start, end);

        return NULL;
    }

    size_t len = end - start;
    Pixel **pixels = malloc(sizeof(Pixel *) * len);
    if (pixels == NULL)
    {
        fprintf(stderr, "ERROR: Cannot allocate memory for pixels. %s\n", strerror(errno));
        return NULL;
    }

    for (size_t i = 0; i < len; i++)
    {
        printf("%d\n", start + i * intervals);

        pixels[i] = from->pixels[start + (i * intervals)];
    }

    return pixels;
}

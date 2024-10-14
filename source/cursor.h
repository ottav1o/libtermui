#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <stdio.h>

typedef struct {
    unsigned short row, col;
} Cursor;

void __tui_cursor_move(unsigned short row, unsigned short col, Cursor *cursor);

#endif // __CURSOR_H__
#include "cursor.h"

#include <stdio.h>

void __tui_cursor_move(unsigned short row, unsigned short col, Cursor *cursor) {
    cursor->row = row;
    cursor->col = col;
}

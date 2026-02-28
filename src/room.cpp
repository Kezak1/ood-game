#include "room.h"

Room::Room() {
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            board[i][j] = Cell();
        }
    }
}
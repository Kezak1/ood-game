#include "game.h"

Game::Game() : p(Player()), pos_r(1), pos_c(1) {
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1) {
                board[i][j] = Cell(WALL); 
            } else {
                board[i][j] = Cell(EMPTY);
            }
        }
    }
}

bool in_range(int r, int c) {
    return r >= 0 && c >= 0 && r < ROWS && c < COLS;
}

void Game::move_player(char c) {
    int new_r = pos_r, new_c = pos_c;
    switch(c) {
        case 'w': //UP
            new_r--;
            break;
        case 's': //DOWN
            new_r++;
            break;
        case 'a': //LEFT
            new_c--;
            break;
        case 'd': //RIGHT
            new_c++;
            break;
        default:
            return;
    }

    if(in_range(new_r, new_c) && board[new_r][new_c].get_c() == EMPTY) {
        pos_r = new_r;
        pos_c = new_c;
    }
}

void Game::render_state() {
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(r == pos_r && c == pos_c) {
                std::cout << C_PLAYER;
                continue;
            }
            switch(board[r][c].get_c()) {
                case WALL:
                    std::cout << C_WALL;
                    break;
                case EMPTY:
                    std::cout << C_EMPTY;
                    break;
                default:
                    std::cout << 'X';
                    break;
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
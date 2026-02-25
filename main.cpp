#include <iostream>

#define ROWS 20
#define COLS 40

constexpr auto WALL = u8"█";
constexpr auto EMPTY = ' ';

int main() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || j == COLS - 1 || i == ROWS - 1) {
                std::cout << WALL;
            }
        }
    }
    return 0;
}
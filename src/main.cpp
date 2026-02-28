#include "constants.h"

#include <iostream>

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

int main() {
    clear_screen();
    std::cout << '\n';
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || j == COLS - 1 || i == ROWS - 1) {
                std::cout << WALL;
            } else {
                std::cout << EMPTY;
            }
        }
        std::cout << '\n';
    }

    while(1) {
        std::cout << "Enter some: ";
        char c;
        std::cin >> c;
        std::cout << c << "\n";

        if(c == 'q') break;
    }

    return 0;
}
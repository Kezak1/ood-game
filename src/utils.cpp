#include "utils.h"

int next_random(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(l, r);

    return dist(gen);
}

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

char read_key() {
    struct termios new_t, old_t;
    tcgetattr(STDIN_FILENO, &old_t);
    
    new_t = old_t;
    new_t.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_t);

    return c;
}
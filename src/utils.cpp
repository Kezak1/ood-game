#include "utils.h"
#include <cctype>

custom_exception::custom_exception(const char* msg) : msg(msg) {}

const char* custom_exception::what() const noexcept {
    return msg.c_str();
}

int next_random(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(l, r);

    return dist(gen);
}

bool in_range(int r, int c) {
    return r >= 0 && c >= 0 && r < ROWS && c < COLS;
}

void full_clear() {
    std::cout << "\033[2J\033[H";
}

void full_clear_from_cursor() {
    std::cout << "\033[J";
}

void clear_line_cursor() {
    std::cout << "\033[2K";
}

void to_start_cursor() {
    std::cout << "\033[H";
}

void hide_cursor() {
    std::cout << "\033[?25l";
}

void unhide_cursor() {
    std::cout << "\033[?25h";
}

void enter_alt_terminal() {
    std::cout << "\033[?1049h";
}

void exit_alt_terminal() {
    std::cout << "\033[?1049l";
}

void set_raw_mode(bool enable) {
    static termios old_t;
    if(enable) {
        termios new_t;
        tcgetattr(STDIN_FILENO, &old_t);
    
        new_t = old_t;
        new_t.c_lflag &= ~(ECHO | ICANON);

        tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    }
}

std::string all_toupper(std::string s) {
    for(auto& c : s) {
        c = toupper(c);
    }
    return s;
}

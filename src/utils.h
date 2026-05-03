#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdexcept>
#include <filesystem>
#include <string>

class custom_exception : public std::exception {
    std::string msg;
public:
    custom_exception(const char* msg);
    const char* what() const noexcept override;
};

inline constexpr int ROWS = 22;
inline constexpr int COLS = 42;

//RIGHT, LEFT, DOWN, UP
inline constexpr int dr[4] = {0, 0, 1, -1};
inline constexpr int dc[4] = {1, -1, 0, 0};

inline constexpr auto C_WALL = "█";
inline constexpr auto C_EMPTY = " ";
inline constexpr auto C_PLAYER = "¶";
inline constexpr auto C_ITEMS = "*";
inline constexpr auto C_ENEMY = "@";

inline constexpr double DEF_MAX = 36.0;

int next_random(int l, int r);
bool in_range(int r, int c);

void full_clear();
void full_clear_from_cursor();
void clear_line_cursor();

void to_start_cursor();

void hide_cursor();
void unhide_cursor();

void enter_alt_terminal();
void exit_alt_terminal();

void set_raw_mode(bool enable);

std::string all_toupper(std::string s); 

struct GameConfig {
    std::string player_name;
    std::filesystem::path log_path;
};

GameConfig load_game_config(const std::filesystem::path& path);

#endif

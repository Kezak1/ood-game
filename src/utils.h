#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <termios.h>
#include <unistd.h>

inline constexpr int ROWS = 22;
inline constexpr int COLS = 42;
inline constexpr int dr[4] = {0, 0, 1, -1};
inline constexpr int dc[4] = {1, -1, 0, 0};

inline constexpr const char* C_WALL = "██";
inline constexpr const char* C_EMPTY = "  ";
inline constexpr const char* C_PLAYER = "¶ ";
inline constexpr const char* C_ITEMS = "!*";


int next_random(int l, int r);
bool in_range(int r, int c);

void full_clear();
void full_clear_from_cursor();
void clear_line_cursor();

void to_start_cursor();

void hide_cursor();
void unhide_cursor();

void set_raw_mode(bool enable);

#endif

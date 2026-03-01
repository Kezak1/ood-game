#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <termios.h>
#include <unistd.h>

inline constexpr int ROWS = 22;
inline constexpr int COLS = 42;
inline constexpr auto C_WALL = "█";
inline constexpr auto C_EMPTY = " ";
inline constexpr auto C_PLAYER = "¶";

int next_random(int l, int r);

void clear_screen();
void to_start_cursor();
void hide_cursor();
void unhide_cursor();

char read_key();

#endif

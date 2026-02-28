#ifndef CONSTANTS_H
#define CONSTANTS_H

inline constexpr int ROWS = 22;
inline constexpr int COLS = 44;
inline constexpr auto C_WALL = "█";
inline constexpr auto C_EMPTY = " ";
inline constexpr auto C_PLAYER = "¶";

enum Cells {
    WALL,
    EMPTY,
    PLAYER,
};

#endif

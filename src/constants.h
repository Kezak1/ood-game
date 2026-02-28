#ifndef CONSTANTS_H
#define CONSTANTS_H

inline constexpr int ROWS = 20;
inline constexpr int COLS = 40;
inline constexpr auto C_WALL = "█";
inline constexpr auto C_EMPTY = " ";
inline constexpr auto C_PLAYER = "¶";

enum cell_icon {
    WALL,
    EMPTY,
    PLAYER,
};

#endif

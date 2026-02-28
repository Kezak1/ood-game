#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "cell.h"
#include "player.h"

#include <iostream>
#include <vector>

class Game {
    Player p;
    int pos_r, pos_c;
    std::vector<std::vector<Cell>> board;
public:
    Game();

    void move_player(char c);
    void render_state();
};

#endif
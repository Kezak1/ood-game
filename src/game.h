#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "room.h"

class Game {
    Player player;
    Room board;
    int gold_cnt;
public:
    Game();
};  

#endif
#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "cell.h"
#include "player.h"


#include "sword.h"
#include "coin.h"
#include "gold.h"
#include "old_book.h"
#include "rock.h"

#include <iostream>
#include <format>
#include <vector>
#include <sstream>

class Game {
    Player p;
    int pos_r, pos_c;
    std::vector<std::vector<Cell>> board;
public:
    Game();
    
    void main_loop();

    void move_player(char c);
    void render_state();
    void cur_action_info();
    
    void player_try_pick_up_item();
    // void player_try_drop_item();
    // void player_try_equip_weapon();
};

#endif
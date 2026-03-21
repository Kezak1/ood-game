#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "cell.h"
#include "player.h"
#include "dungeon_builder.h"

#include "sword.h"
#include "bow.h"
#include "axe.h"
#include "strange_idol.h"
#include "old_book.h"
#include "rock.h"
#include "coin.h"
#include "gold.h"

#include <functional>
#include <iostream>
#include <format>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <map>

class Game {
    Player p;
    int pos_r, pos_c;
    std::vector<std::vector<Cell>> board;
    std::unordered_map<char, std::function<bool()>> actions;
public:
    Game();
    void main_loop();
private:
    void init_actions();

    void move_player(char c);
    void render_state();
    void cur_action_info();

    void print_player_stats();
    void print_player_wallet();
    void print_player_inventory();
    void print_player_hands();
    
    void player_try_pick_up_item();
    void player_try_drop_item();
    void player_try_equip_weapon();
    void player_try_unequip_weapon();
    void player_try_get_item_info();
};

#endif
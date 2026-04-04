#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "cell.h"
#include "dungeon_builder.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"

#include "sword.h"
#include "bow.h"
#include "axe.h"
#include "strange_idol.h"
#include "old_book.h"
#include "rock.h"
#include "coin.h"
#include "gold.h"

#include "action_handler.h"
#include "move_handler.h"
#include "inventory_handler.h"
#include "equipment_handler.h"

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
    std::vector<Enemy> enemies;
    std::vector<std::vector<int>> enemy_map;
    
    std::vector<std::vector<Cell>> board;
    PlayerCapabilities capabilities;

    std::vector<std::unique_ptr<ActionHandler>> handlers;
public:
    Game();
    void main_loop();

    void player_move_up();
    void player_move_down();
    void player_move_left();
    void player_move_right();

    void player_try_pick_up_item();
    void player_try_drop_item();
    void player_try_equip_weapon();
    void player_try_unequip_weapon();
    void player_try_get_item_info();
private:
    void init_handlers();
    void render_state();
    void cur_action_info();

    void print_player_stats();
    void print_player_wallet();
    void print_player_inventory();
    void print_player_hands();
    void print_instructions();

    bool is_enemy_pos(int r, int c);
};

#endif
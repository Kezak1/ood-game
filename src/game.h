#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "cell.h"
#include "dungeon_builder.h"
#include "file_logger.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"

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

    Logger& logger;
    std::filesystem::path log_file;
public:
    Game(Logger&, std::string, std::filesystem::path);
    void main_loop();
    bool battle();
    void show_full_log_history();

    void player_move(int dr, int dc, std::string direction);
    void player_move_up();
    void player_move_down();
    void player_move_left();
    void player_move_right();

    void player_try_pick_up_item();
    void player_try_drop_item();
    void player_try_equip_weapon();
    void player_try_unequip_weapon();
    void player_try_get_item_info();

    int player_enemy_map_value();
private:
    void init_board();
    void init_handlers();
    void render_state();
    void render_battle_state(int enemy_idx);
    void cur_action_info();

    void print_battlefield();
    void print_player_stats();
    void print_player_wallet();
    void print_player_inventory();
    void print_player_hands();
    void print_board_with_recent_logs();
    
    void print_instructions();
    void print_enemy_hp(int enemy_idx); 

    bool is_enemy_pos(int r, int c);
    bool player_has_equipped_item() const;
    const Item* choose_battle_item() const;
    std::unique_ptr<Attack> choose_battle_attack() const;
    void remove_enemy_from_map(int enemy_idx);    
};

#endif
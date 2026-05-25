#pragma once

#include "player.h"
#include "cell.h"
#include "enemy.h"
#include "dungeon_builder.h"

#include <memory>
#include <string>
#include <vector>

struct RoundResult;

class GameModel {
    Player p;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::vector<int>> enemy_map;
    
    std::vector<std::vector<Cell>> board;
    PlayerCapabilities capabilities;
public:
    GameModel(std::string player_name, BuildResult&& res);

    void player_move(int dr, int dc, std::string direction);
    void player_move_up();
    void player_move_down();
    void player_move_left();
    void player_move_right();

    void player_try_pick_up_item(int idx);
    void player_try_drop_item(int idx);
    void player_try_equip_weapon(int idx);
    void player_try_unequip_weapon(std::string hand);
    
    bool check_battle_start(int enemy_idx);
    RoundResult battle_round(int enemy_idx, const Item& item, const Attack& attack);
    void player_give_up(int enemy_idx);

    void enemies_take_turn();
    void kill_enemy(int enemy_idx);

    bool is_enemy_pos(int r, int c) const;
    int player_enemy_map_value() const;
    bool player_has_equipped_item() const;
    
    Player& player();
    const Player& player() const;

    Cell& cell_at(int r, int c);
    const Cell& cell_at(int r, int c) const;

    const std::vector<std::vector<Cell>>& get_board() const;
    const std::vector<std::unique_ptr<Enemy>>& get_enemies() const;
    PlayerCapabilities get_capabilities() const;
};

struct RoundResult {
    int player_dmg_dealt;
    int enemy_dmg_dealt;

    bool player_died;
    bool enemy_died;
};

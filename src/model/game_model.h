#pragma once

#include "dto.h"
#include "player.h"
#include "cell.h"
#include "enemy.h"
#include "dungeon_builder.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

struct RoundResult;

class GameModel {
    std::map<int, Player> players;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::vector<Cell>> board;
    std::map<int, int> battles;
    PlayerCapabilities capabilities;

    std::vector<std::vector<int>> enemy_map;
    std::vector<std::vector<int>> player_map;

    GameModel(const GameStateDto& dto);
public:
    GameModel(BuildResult&& res);

    void player_try_move(int player_id, std::string direction);
    void player_try_pick_up_item(int player_id, int idx);
    void player_try_drop_item(int player_id, int idx);
    void player_try_equip_item(int player_id, int idx);
    void player_try_unequip_item(int player_id, std::string hand);
    bool player_try_start_battle(int player_id);

    RoundResult battle_round(int player_id, const Item& item, const Attack& attack);
    void player_give_up(int player_id);
    bool is_player_in_battle(int player_id) const;
    bool is_enemy_in_batlte(int enemy_idx) const;
    void end_battle(int player);

    bool add_player(int player_id, std::string name);
    bool remove_player(int player_id);

    void enemies_take_turn();
    void kill_enemy(int enemy_idx);

    bool is_enemy_pos(int r, int c) const;
    int enemy_map_value(int player_id) const;
    int player_map_value(int r, int c) const;
    bool player_has_equipped_item(int player_id) const;
    
    Player& player(int player_id);
    const Player& player(int player_id) const;

    Cell& cell_at(int r, int c);
    const Cell& cell_at(int r, int c) const;

    const Enemy& get_battled_enemy(int player_id) const;
    const std::vector<std::vector<Cell>>& get_board() const;
    const std::map<int, Player>& get_players() const;
    const std::vector<std::unique_ptr<Enemy>>& get_enemies() const;
    const std::map<int, int>& get_battles() const;
    PlayerCapabilities get_capabilities() const;
private:
    std::pair<int, int> get_player_starting_pos();
};

struct RoundResult {
    int player_dmg_dealt;
    int enemy_dmg_dealt;

    bool player_died;
    bool enemy_died;
};

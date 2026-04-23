#ifndef DUNGEON_BUILDER_H
#define DUNGEON_BUILDER_H

#include "cell.h"
#include "strong_modifier.h"
#include "unlucky_modifier.h"
#include "enemy.h"

#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <climits>

struct PlayerCapabilities {
    bool can_move = false;
    bool has_items = false;
    bool has_weapons = false;
    bool has_enemies = false;
};

struct BuildResult {
    std::vector<std::vector<Cell>> board;
    std::vector<Enemy> enemies;
    PlayerCapabilities capabilities;
};

class DungeonBuilder {
    int player_start_pos_r, player_start_pos_c;
    
    std::vector<Enemy> enemies;
    std::vector<std::vector<Cell>> board;
    PlayerCapabilities capabilities;
public:
    DungeonBuilder(bool start_filled = true);
    BuildResult build();
private:
    void init_board(bool start_filled);
    void modifier_tester_setup();

    std::vector<std::pair<int, int>> get_all_empty_pos();
    
    void add_random_path();
    void add_random_chamber(int len);
    void add_center_room(int w, int h);

    void add_random_items(int count = 5);
    void add_random_weapons(int count = 5);
    
    void add_random_enemies(int count = 5);
    void add_random_currencies(int count = 5);

    void connect_rooms();
};

#endif
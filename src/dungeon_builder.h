#pragma once

#include "cell.h"
#include "dungeon_theme_factory.h"
#include "strong_modifier.h"
#include "unlucky_modifier.h"
#include "enemy.h"

#include <memory>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <climits>

struct PlayerCapabilities {
    bool can_move = false;
    bool has_items = false;
    bool has_currency = false;
    bool has_enemies = false;
};

struct BuildResult {
    std::vector<std::vector<Cell>> board;
    std::vector<Enemy> enemies;
    std::string begining_msg;
    PlayerCapabilities capabilities;
};

class DungeonBuilder {
    int player_start_pos_r, player_start_pos_c;
    
    std::vector<Enemy> enemies;
    std::vector<std::vector<Cell>> board;
    PlayerCapabilities capabilities;

    friend class DungeonBuilderFacade;
public:
    DungeonBuilder(bool start_filled);
    BuildResult build(const DungeonThemeFactory&);
private:
    void init_board(bool start_filled);
    void modifier_tester_setup();

    std::vector<std::pair<int, int>> get_empty_pos();
    std::vector<std::pair<int, int>> get_no_items_pos();
    
    void add_random_path();
    void add_random_chamber(int len);
    void add_center_room(int w, int h);

    void add_item(int r, int c, std::unique_ptr<Item> item);
    void add_random_junks(int count);
    void add_random_weapons(int count);
    void add_random_currencies(int count);
    
    void add_enemy(Enemy enemy);
    void add_random_enemies(int count);
    
    void connect_empty();
};

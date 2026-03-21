#ifndef DUNGEON_BUILDER_H
#define DUNGEON_BUILDER_H

#include "cell.h"

#include <vector>

class DungeonBuilder {
    std::vector<std::vector<Cell>> board;
public:
    DungeonBuilder();
    std::vector<std::vector<Cell>> build();
private:
    void init_board();

    std::vector<std::pair<int, int>> get_all_empty_pos();

    void empty_dungeon();
    void fill_dungeon();
    
    void add_random_path();
    void add_random_chamber(int len);
    void add_center_room(int w, int h);

    void add_random_items(int count = 5);
    void add_random_weapons(int count = 5);

    void connect_rooms();
};

#endif
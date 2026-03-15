#ifndef DUNGEON_H
#define DUNGEON_H

#include "cell.h"

#include <vector>

class Dungeon {
    std::vector<std::vector<Cell>> board;
public:
    Dungeon();
    std::vector<std::vector<Cell>>& get_board();
    const std::vector<std::vector<Cell>>& get_board() const;
    
    void empty_dungeon();
    void fill_dungeon();
    
    void add_random_path(int len);
    // void add_random_paths(int l, int r);

    void add_random_chamber(int len);
    // void add_random_chambers(int l, int r);

    void add_center_room(int w, int h);

    void add_random_items(int count = 5);
    void add_random_weapons(int count = 5);

    void connect_rooms();
private:
    std::vector<std::pair<int, int>> get_all_empty_pos();
};

#endif
#pragma once

#include <vector>
#include <utility>

class DungeonBuilder;
class Item;

class DungeonBuilderFacade {
    DungeonBuilder& builder;

    DungeonBuilderFacade(DungeonBuilder& builder);
    friend class DungeonBuilder;
public:
    std::vector<std::pair<int, int>> get_empty_pos();
    std::vector<std::pair<int, int>> get_no_items_pos();
    
    void add_random_path();
    void add_random_chamber(int len);
    void add_center_room(int w, int h);    
    void connect_empty();
};

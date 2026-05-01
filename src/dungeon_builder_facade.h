#ifndef DUNGEON_THEME_TOOLS_H
#define DUNGEON_THEME_TOOLS_H

#include <memory>
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

    void add_item(int r, int c, std::unique_ptr<Item> item);
    void add_random_junks(int count);
    void add_random_weapons(int count);
    void add_random_currencies(int count);
    
    void add_enemy(std::string name, int r, int c, int attack, int armor, int hp);
    void add_random_enemies(int count);
    
    void connect_empty();
};

#endif
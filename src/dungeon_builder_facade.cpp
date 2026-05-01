#include "dungeon_builder_facade.h"
#include "dungeon_builder.h"


DungeonBuilderFacade::DungeonBuilderFacade(DungeonBuilder &builder)
    : builder(builder) {}

std::vector<std::pair<int, int>> DungeonBuilderFacade::get_empty_pos() {
    return builder.get_empty_pos();
}

std::vector<std::pair<int, int>> DungeonBuilderFacade::get_no_items_pos() {
    return builder.get_no_items_pos();
}


void DungeonBuilderFacade::add_random_path() {
    builder.add_random_path();
}

void DungeonBuilderFacade::add_random_chamber(int len) {
    builder.add_random_chamber(len);
}

void DungeonBuilderFacade::add_center_room(int w, int h) {
    builder.add_center_room(w, h);
}

void DungeonBuilderFacade::add_item(int r, int c, std::unique_ptr<Item> item) {
    builder.add_item(r, c, std::move(item));
}

void DungeonBuilderFacade::add_random_junks(int count) {
    builder.add_random_junks(count);
}

void DungeonBuilderFacade::add_random_weapons(int count) {
    builder.add_random_weapons(count);
}

void DungeonBuilderFacade::add_random_currencies(int count) {
    builder.add_random_currencies(count);
}
    
void DungeonBuilderFacade::add_enemy(std::string name, int r, int c, int attack, int armor, int hp) {
    builder.add_enemy(name, r, c, attack, armor, hp);
}

void DungeonBuilderFacade::add_random_enemies(int count) {
    builder.add_random_enemies(count);
}

void DungeonBuilderFacade::connect_empty() {
    builder.connect_empty();
}
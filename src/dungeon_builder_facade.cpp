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

void DungeonBuilderFacade::connect_empty() {
    builder.connect_empty();
}
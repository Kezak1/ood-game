#include "mystic_modifier.h"


MysticModifier::MysticModifier(std::unique_ptr<Item> item) 
    : ItemModifier(std::move(item), "mystic") {
}

int MysticModifier::get_wis_bonus() const {
    return ItemModifier::get_wis_bonus() + 5;
}
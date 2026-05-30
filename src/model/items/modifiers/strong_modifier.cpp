#include "strong_modifier.h"
#include "item_modifier.h"

StrongModifier::StrongModifier(std::unique_ptr<Item> item) 
    : ItemModifier(std::move(item), "strong") {
}

int StrongModifier::get_dmg() const {
    return ItemModifier::get_dmg() + 5;
}

std::string StrongModifier::get_info() const {
    return std::format("{}+{}", ItemModifier::get_info(), 5);
}
#include "unlucky_modifier.h"
#include "item_modifier.h"
#include <string>

UnluckyModifier::UnluckyModifier(std::unique_ptr<Item> item) 
    : ItemModifier(std::move(item), "unlucky") {
}

int UnluckyModifier::get_lck_bonus() const {
    return ItemModifier::get_lck_bonus() - 5;
}
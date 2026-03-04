#include "item.h"
#include "player.h"

Item::Item(std::string s) : name(s) {
}

const std::string& Item::get_name() {
    return name;
}

bool Item::carryable(Player&) const {
    return true;
}

bool Item::isweapon() const {
    return false;
}
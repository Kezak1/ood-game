#include "weapon.h"

Weapon::Weapon(int _dmg, std::string s) : Item(s), dmg(_dmg) {}

std::string Weapon::get_stats() const {
    std::stringstream res;
    res << ", dmg: " << dmg;
    return res.str();
}

std::string Weapon::get_info() const {
    return "weapon (unequippable)";
}
#include "weapon.h"

Weapon::Weapon(int _dmg, std::string s) : Item(s), dmg(_dmg) {}

std::string Weapon::get_info() const {
    return "weapon (unequippable)";
}
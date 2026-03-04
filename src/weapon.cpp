#include "weapon.h"

Weapon::Weapon(int _dmg, weapon_hold _hold, std::string s) : Item(s), dmg(_dmg), hold(_hold) {}

bool Weapon::isweapon() const {
    return true;
}

const weapon_hold& Weapon::get_hold() const {
    return hold;
}
#include "weapon.h"

Weapon::Weapon(int _dmg, std::string s) : Item(s), dmg(_dmg) {}

int Weapon::get_dmg() const {
    return dmg;
}
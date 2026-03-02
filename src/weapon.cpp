#include "weapon.h"

Weapon::Weapon(int _dmg, weapon_hold _hold, std::string s) : Item(s), dmg(_dmg), hold(_hold) {}
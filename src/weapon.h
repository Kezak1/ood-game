#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

enum class weapon_hold {
    SINGLE,
    BOTH,
};

class Weapon : public Item {
    int dmg;
    weapon_hold hold;
public:
    Weapon(int _dmg, weapon_hold _hold, std::string s);
};

#endif
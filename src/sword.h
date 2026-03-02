#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"

class Sword : public Weapon {
public:
    Sword(int _dmg, std::string s);
};

#endif
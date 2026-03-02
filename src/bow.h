#ifndef BOW_H
#define BOW_H

#include "weapon.h"

class Bow : public Weapon {
public:
    Bow(int _dmg, std::string s);
};

#endif
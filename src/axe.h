#ifndef AXE_H
#define AXE_H

#include "weapon.h"

class Axe : public Weapon {
public:
    Axe(int _dmg, std::string s);
};

#endif
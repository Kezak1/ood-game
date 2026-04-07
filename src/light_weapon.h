#ifndef LIGHT_WEAPON_H
#define LIGHT_WEAPON_H

#include "weapon.h"

class LightWeapon : public Weapon {
public:
    LightWeapon(int dmg, std::string name);
    int attack(const Player& p, const Attack& a) const override;
    int defense(const Player& p, const Attack& a) const override;
};

#endif
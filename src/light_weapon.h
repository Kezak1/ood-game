#ifndef LIGHT_WEAPON_H
#define LIGHT_WEAPON_H

#include "weapon.h"

class LightWeapon : public Weapon {
public:
    LightWeapon(int dmg, std::string name);
    int accept_attack(const Player& p,  const Attack& a, const Item& stats) const override;
    int accept_defense(const Player& p, const Attack& a, const Item& stats) const override;
};

#endif
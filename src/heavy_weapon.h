#ifndef HEAVY_WEAPON_H
#define HEAVY_WEAPON_H

#include "weapon.h"

class HeavyWeapon : public Weapon {
public:
    HeavyWeapon(int dmg, std::string name);
    int accept_attack(const Player& p,  const Attack& a, const Item& stats) const override;
    int accept_defense(const Player& p, const Attack& a, const Item& stats) const override;
};

#endif
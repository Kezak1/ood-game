#ifndef HEAVY_WEAPON_H
#define HEAVY_WEAPON_H

#include "weapon.h"

class HeavyWeapon : public Weapon {
public:
    HeavyWeapon(int dmg, std::string name);
    int attack_dispatched(const Player& p,  const Attack& a, const Item& stats) const override;
    int defense_dispatched(const Player& p, const Attack& a, const Item& stats) const override;
};

#endif
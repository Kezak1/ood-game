#ifndef HEAVY_WEAPON_H
#define HEAVY_WEAPON_H

#include "weapon.h"

class HeavyWeapon : public Weapon {
public:
    HeavyWeapon(int dmg, std::string name);
    int attack(const Player& p,  const Attack& a) const override;
    int defense(const Player& p, const Enemy& e, const Attack& a) const override;
};

#endif
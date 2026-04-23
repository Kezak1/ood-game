#ifndef MAGICAL_WEAPON_H
#define MAGICAL_WEAPON_H

#include "weapon.h"

class MagicalWeapon : public Weapon {
public:
    MagicalWeapon(int dmg, std::string name);
    int attack_dispatched(const Player& p,  const Attack& a, const Item& stats) const override;
    int defense_dispatched(const Player& p, const Attack& a, const Item& stats) const override;
};

#endif
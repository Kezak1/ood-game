#pragma once

#include "weapon.h"

class MagicalWeapon : public Weapon {
public:
    MagicalWeapon(int dmg, std::string name);
    int accept_attack(const Player& p,  const Attack& a, const Item& stats) const override;
    int accept_defense(const Player& p, const Attack& a, const Item& stats) const override;
    int sound_range() const override;
};

#ifndef MAGICAL_WEAPON_H
#define MAGICAL_WEAPON_H

#include "weapon.h"

class MagicalWeapon : public Weapon {
public:
    MagicalWeapon(int dmg, std::string name);
    int attack(const Player& p, const Attack& a) const override;
    int defense(const Player& p, const Enemy& e, const Attack& a) const override;
};

#endif
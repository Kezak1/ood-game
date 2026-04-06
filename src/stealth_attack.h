#ifndef STEALTH_ATTACK_H
#define STEALTH_ATTACK_H

#include "attack.h"

class SlealthAttack : public Attack {
    int attack_dmg(const Player&, const HeavyWeapon&) const override;
    int attack_dmg(const Player&, const LightWeapon&) const override;
    int attack_dmg(const Player&, const MagicalWeapon&) const override;
    int attack_dmg(const Player&, const Item&) const override;

    double defense_ratio(const Player&, const HeavyWeapon&) const override;
    double defense_ratio(const Player&, const LightWeapon&) const override;
    double defense_ratio(const Player&, const MagicalWeapon&) const override;
    double defense_ratio(const Player&, const Item&) const override;
};

#endif
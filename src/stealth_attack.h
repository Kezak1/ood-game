#ifndef STEALTH_ATTACK_H
#define STEALTH_ATTACK_H

#include "attack.h"

class StealthAttack : public Attack {
    int attack_pts(const Player&, const HeavyWeapon&, const Item&) const override;
    int attack_pts(const Player&, const LightWeapon&, const Item&) const override;
    int attack_pts(const Player&, const MagicalWeapon&, const Item&) const override;
    int attack_pts(const Player&, const Item&, const Item&) const override;

    int defense_pts(const Player&, const HeavyWeapon&, const Item&) const override;
    int defense_pts(const Player&, const LightWeapon&, const Item&) const override;
    int defense_pts(const Player&, const MagicalWeapon&, const Item&) const override;
    int defense_pts(const Player&, const Item&, const Item&) const override;
};

#endif
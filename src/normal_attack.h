#ifndef NORMAL_ATTACK_H
#define NORMAL_ATTACK_H

#include "attack.h"

class NormalAttack : public Attack {
    int attack_pts(const Player&, const HeavyWeapon&) const override;
    int attack_pts(const Player&, const LightWeapon&) const override;
    int attack_pts(const Player&, const MagicalWeapon&) const override;
    int attack_pts(const Player&, const Item&) const override;

    int defense_pts(const Player&, const HeavyWeapon&) const override;
    int defense_pts(const Player&, const LightWeapon&) const override;
    int defense_pts(const Player&, const MagicalWeapon&) const override;
    int defense_pts(const Player&, const Item&) const override;
};

#endif
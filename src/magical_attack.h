#ifndef MAGICAL_ATTACK_H
#define MAGICAL_ATTACK_H

#include "attack.h"

class MagicalAttack : public Attack {
    int visit_attack(const Player&, const HeavyWeapon&, const Item&) const override;
    int visit_attack(const Player&, const LightWeapon&, const Item&) const override;
    int visit_attack(const Player&, const MagicalWeapon&, const Item&) const override;
    int visit_attack(const Player&, const Item&, const Item&) const override;

    int visit_defense(const Player&, const HeavyWeapon&, const Item&) const override;
    int visit_defense(const Player&, const LightWeapon&, const Item&) const override;
    int visit_defense(const Player&, const MagicalWeapon&, const Item&) const override;
    int visit_defense(const Player&, const Item&, const Item&) const override;
};

#endif
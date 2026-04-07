#include "magical_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int MagicalAttack::attack_pts(const Player&, const HeavyWeapon&) const {
   return 1;
}

int MagicalAttack::attack_pts(const Player&, const LightWeapon&) const {
    return 1;
}

int MagicalAttack::attack_pts(const Player& p, const MagicalWeapon& w) const {
    return p.get_wis() + w.get_dmg();
}

int MagicalAttack::attack_pts(const Player&, const Item&) const {
    return 0;
}

int MagicalAttack::defense_pts(const Player& p, const HeavyWeapon&) const {
    return p.get_lck();
}

int MagicalAttack::defense_pts(const Player& p, const LightWeapon&) const {
    return p.get_lck();
}

int MagicalAttack::defense_pts(const Player& p, const MagicalWeapon&) const {
    return 2 * p.get_wis();
}

int MagicalAttack::defense_pts(const Player& p, const Item&) const {
    return p.get_lck();
}
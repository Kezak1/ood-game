#include "normal_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int NormalAttack::attack_pts(const Player& p, const HeavyWeapon& w) const {
    return (p.get_str() + p.get_agr()) / 2 + w.get_dmg();
}

int NormalAttack::attack_pts(const Player& p, const LightWeapon& w) const {
    return (p.get_dex() + p.get_lck()) / 2 + w.get_dmg();
}

int NormalAttack::attack_pts(const Player&, const MagicalWeapon&) const {
    return 1;
}

int NormalAttack::attack_pts(const Player&, const Item&) const {
    return 0;
}

int NormalAttack::defense_pts(const Player& p, const HeavyWeapon&) const {
    return p.get_str() + p.get_lck();
}

int NormalAttack::defense_pts(const Player& p, const LightWeapon&) const {
    return p.get_dex() + p.get_lck();
}

int NormalAttack::defense_pts(const Player& p, const MagicalWeapon&) const {
    return p.get_dex() + p.get_lck();
}

int NormalAttack::defense_pts(const Player& p, const Item&) const {
    return p.get_dex();
}
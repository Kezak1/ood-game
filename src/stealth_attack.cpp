#include "stealth_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int SlealthAttack::attack_pts(const Player& p, const HeavyWeapon& w) const {
    return (p.get_str() + p.get_agr()) / 4 + w.get_dmg() / 2;
}

int SlealthAttack::attack_pts(const Player& p, const LightWeapon& w) const {
    return (p.get_dex() + p.get_lck()) + 2 * w.get_dmg();
}

int SlealthAttack::attack_pts(const Player&, const MagicalWeapon&) const {
    return 1;
}

int SlealthAttack::attack_pts(const Player&, const Item&) const {
    return 0;
}

int SlealthAttack::defense_pts(const Player& p, const HeavyWeapon&) const {
    return p.get_str();
}

int SlealthAttack::defense_pts(const Player& p, const LightWeapon&) const {
    return p.get_dex();
}

int SlealthAttack::defense_pts(const Player&, const MagicalWeapon&) const {
    return 0;
}

int SlealthAttack::defense_pts(const Player&, const Item&) const {
    return 0;
}
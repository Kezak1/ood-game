#include "magical_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int MagicalAttack::attack_dmg(const Player& p, const HeavyWeapon& w) const {
   return 1;
}

int MagicalAttack::attack_dmg(const Player& p, const LightWeapon& w) const {
    return 1;
}

int MagicalAttack::attack_dmg(const Player& p, const MagicalWeapon& w) const {
    return p.get_wis() + w.get_dmg();
}

int MagicalAttack::attack_dmg(const Player&, const Item&) const {
    return 0;
}

double MagicalAttack::defense_ratio(const Player& p, const HeavyWeapon&) const {
    return (double)(p.get_lck()) / DEF_MAX;
}

double MagicalAttack::defense_ratio(const Player& p, const LightWeapon&) const {
    return (double)(p.get_lck()) / DEF_MAX;
}

double MagicalAttack::defense_ratio(const Player& p, const MagicalWeapon&) const {
    return (double)(2 * p.get_wis()) / DEF_MAX;
}

double MagicalAttack::defense_ratio(const Player& p, const Item&) const {
    return (double)(p.get_lck()) / DEF_MAX;
}
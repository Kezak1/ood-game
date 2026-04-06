#include "stealth_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int SlealthAttack::attack_dmg(const Player& p, const HeavyWeapon& w) const {
    return (p.get_str() + p.get_agr()) / 4 + w.get_dmg() / 2;
}

int SlealthAttack::attack_dmg(const Player& p, const LightWeapon& w) const {
    return (p.get_dex() + p.get_lck()) + 2 * w.get_dmg();
}

int SlealthAttack::attack_dmg(const Player&, const MagicalWeapon&) const {
    return 1;
}

int SlealthAttack::attack_dmg(const Player&, const Item&) const {
    return 0;
}

double SlealthAttack::defense_ratio(const Player& p, const HeavyWeapon&) const {
    return (double)(p.get_str()) / DEF_MAX;
}

double SlealthAttack::defense_ratio(const Player& p, const LightWeapon&) const {
    return (double)(p.get_dex()) / DEF_MAX;
}

double SlealthAttack::defense_ratio(const Player&, const MagicalWeapon&) const {
    return 0.0;
}

double SlealthAttack::defense_ratio(const Player& p, const Item&) const {
    return 0.0;
}
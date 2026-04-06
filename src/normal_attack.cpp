#include "normal_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int NormalAttack::attack_dmg(const Player& p, const HeavyWeapon& w) const {
    return (p.get_str() + p.get_agr()) / 2 + w.get_dmg();
}

int NormalAttack::attack_dmg(const Player& p, const LightWeapon& w) const {
    return (p.get_dex() + p.get_lck()) / 2 + w.get_dmg();
}

int NormalAttack::attack_dmg(const Player&, const MagicalWeapon&) const {
    return 1;
}

int NormalAttack::attack_dmg(const Player&, const Item&) const {
    return 0;
}

double NormalAttack::defense_ratio(const Player& p, const HeavyWeapon&) const {
    return (double)(p.get_str() + p.get_lck()) / DEF_MAX;
}

double NormalAttack::defense_ratio(const Player& p, const LightWeapon&) const {
    return (double)(p.get_dex() + p.get_lck()) / DEF_MAX;
}

double NormalAttack::defense_ratio(const Player& p, const MagicalWeapon&) const {
    return (double)(p.get_dex() + p.get_lck()) / DEF_MAX;
}

double NormalAttack::defense_ratio(const Player& p, const Item&) const {
    return (double)(p.get_dex()) / DEF_MAX;
}
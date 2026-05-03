#include "normal_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int NormalAttack::visit_attack(const Player& p, const HeavyWeapon&, const Item& stats) const {
    return (p.get_str() + p.get_agr()) / 2 + stats.get_dmg();
}

int NormalAttack::visit_attack(const Player& p, const LightWeapon&, const Item& stats) const {
    return (p.get_dex() + p.get_lck()) / 2 + stats.get_dmg();
}

int NormalAttack::visit_attack(const Player&, const MagicalWeapon&, const Item&) const {
    return 1;
}

int NormalAttack::visit_attack(const Player&, const Item&, const Item&) const {
    return 0;
}

int NormalAttack::visit_defense(const Player& p, const HeavyWeapon&, const Item&) const {
    return p.get_str() + p.get_lck();
}

int NormalAttack::visit_defense(const Player& p, const LightWeapon&, const Item&) const {
    return p.get_dex() + p.get_lck();
}

int NormalAttack::visit_defense(const Player& p, const MagicalWeapon&, const Item&) const {
    return p.get_dex() + p.get_lck();
}

int NormalAttack::visit_defense(const Player& p, const Item&, const Item&) const {
    return p.get_dex();
}
#include "stealth_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int StealthAttack::visit_attack(const Player& p, const HeavyWeapon&, const Item& stats) const {
    return (p.get_str() + p.get_agr()) / 4 + stats.get_dmg() / 2;
}

int StealthAttack::visit_attack(const Player& p, const LightWeapon&, const Item& stats) const {
    return (p.get_dex() + p.get_lck()) + 2 * stats.get_dmg();
}

int StealthAttack::visit_attack(const Player&, const MagicalWeapon&, const Item&) const {
    return 1;
}

int StealthAttack::visit_attack(const Player&, const Item&, const Item&) const {
    return 0;
}

int StealthAttack::visit_defense(const Player& p, const HeavyWeapon&, const Item&) const {
    return p.get_str();
}

int StealthAttack::visit_defense(const Player& p, const LightWeapon&, const Item&) const {
    return p.get_dex();
}

int StealthAttack::visit_defense(const Player&, const MagicalWeapon&, const Item&) const {
    return 0;
}

int StealthAttack::visit_defense(const Player&, const Item&, const Item&) const {
    return 0;
}
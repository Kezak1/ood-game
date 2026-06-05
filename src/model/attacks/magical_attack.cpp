#include "magical_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int MagicalAttack::visit_attack(const Player&, const HeavyWeapon&, const Item&) const {
   return 1;
}

int MagicalAttack::visit_attack(const Player&, const LightWeapon&, const Item&) const {
    return 1;
}

int MagicalAttack::visit_attack(const Player& p, const MagicalWeapon&, const Item& stats) const {
    return p.get_wis() + stats.get_dmg();
}

int MagicalAttack::visit_attack(const Player&, const Item&, const Item&) const {
    return 0;
}

int MagicalAttack::visit_defense(const Player& p, const HeavyWeapon&, const Item&) const {
    return p.get_lck();
}

int MagicalAttack::visit_defense(const Player& p, const LightWeapon&, const Item&) const {
    return p.get_lck();
}

int MagicalAttack::visit_defense(const Player& p, const MagicalWeapon&, const Item&) const {
    return 2 * p.get_wis();
}

int MagicalAttack::visit_defense(const Player& p, const Item&, const Item&) const {
    return p.get_lck();
}
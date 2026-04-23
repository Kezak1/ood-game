#include "stealth_attack.h"

#include "heavy_weapon.h"
#include "light_weapon.h"
#include "magical_weapon.h"
#include "item.h"

int StealthAttack::attack_pts(const Player& p, const HeavyWeapon&, const Item& stats) const {
    return (p.get_str() + p.get_agr()) / 4 + stats.get_dmg() / 2;
}

int StealthAttack::attack_pts(const Player& p, const LightWeapon&, const Item& stats) const {
    return (p.get_dex() + p.get_lck()) + 2 * stats.get_dmg();
}

int StealthAttack::attack_pts(const Player&, const MagicalWeapon&, const Item&) const {
    return 1;
}

int StealthAttack::attack_pts(const Player&, const Item&, const Item&) const {
    return 0;
}

int StealthAttack::defense_pts(const Player& p, const HeavyWeapon&, const Item&) const {
    return p.get_str();
}

int StealthAttack::defense_pts(const Player& p, const LightWeapon&, const Item&) const {
    return p.get_dex();
}

int StealthAttack::defense_pts(const Player&, const MagicalWeapon&, const Item&) const {
    return 0;
}

int StealthAttack::defense_pts(const Player&, const Item&, const Item&) const {
    return 0;
}
#include "magical_weapon.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "attack.h"

#include <algorithm>

MagicalWeapon::MagicalWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int MagicalWeapon::attack(const Player& p, const Attack& a) const {
    return a.attack_dmg(p, *this);
}

int MagicalWeapon::defense(const Player& p, const Enemy& e, const Attack& a) const {
    return e.get_attack() * 0.5 * std::clamp(a.defense_ratio(p, *this), 0.0, 1.0);
}
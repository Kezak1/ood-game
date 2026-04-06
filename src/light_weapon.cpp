#include "light_weapon.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "attack.h"

#include <algorithm>

LightWeapon::LightWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int LightWeapon::attack(const Player& p, const Attack& a) const {
    return a.attack_dmg(p, *this);
}

int LightWeapon::defense(const Player& p, const Enemy& e, const Attack& a) const {
    return e.get_attack() * 0.5 * std::clamp(a.defense_ratio(p, *this), 0.0, 1.0);
}
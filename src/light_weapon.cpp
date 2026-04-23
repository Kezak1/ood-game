#include "light_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

LightWeapon::LightWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int LightWeapon::attack_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.attack_pts(p, *this, stats);
}

int LightWeapon::defense_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.defense_pts(p, *this, stats);
}
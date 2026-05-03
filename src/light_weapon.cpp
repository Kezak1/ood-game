#include "light_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

LightWeapon::LightWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int LightWeapon::accept_attack(const Player& p, const Attack& a, const Item& stats) const {
    return a.visit_attack(p, *this, stats);
}

int LightWeapon::accept_defense(const Player& p, const Attack& a, const Item& stats) const {
    return a.visit_defense(p, *this, stats);
}
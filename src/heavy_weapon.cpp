#include "heavy_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

HeavyWeapon::HeavyWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int HeavyWeapon::accept_attack(const Player& p,  const Attack& a, const Item& stats) const {
    return a.visit_attack(p, *this, stats);
}

int HeavyWeapon::accept_defense(const Player& p, const Attack& a, const Item& stats) const {
    return a.visit_defense(p, *this, stats);
}
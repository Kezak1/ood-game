#include "heavy_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

HeavyWeapon::HeavyWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int HeavyWeapon::attack_dispatched(const Player& p,  const Attack& a, const Item& stats) const {
    return a.attack_pts(p, *this, stats);
}

int HeavyWeapon::defense_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.defense_pts(p, *this, stats);
}
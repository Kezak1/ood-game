#include "magical_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

MagicalWeapon::MagicalWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int MagicalWeapon::attack_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.attack_pts(p, *this, stats);
}

int MagicalWeapon::defense_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.defense_pts(p, *this, stats);
}
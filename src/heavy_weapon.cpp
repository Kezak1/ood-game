#include "heavy_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

HeavyWeapon::HeavyWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int HeavyWeapon::attack(const Player& p, const Attack& a) const {
    return a.attack_pts(p, *this);
}

int HeavyWeapon::defense(const Player& p, const Attack& a) const {
    return a.defense_pts(p, *this);
}
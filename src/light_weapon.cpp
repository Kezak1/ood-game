#include "light_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

LightWeapon::LightWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int LightWeapon::attack(const Player& p, const Attack& a) const {
    return a.attack_pts(p, *this);
}

int LightWeapon::defense(const Player& p, const Attack& a) const {
    return a.defense_pts(p, *this);
}
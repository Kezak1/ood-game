#include "magical_weapon.h"
#include "weapon.h"
#include "player.h"
#include "attack.h"

MagicalWeapon::MagicalWeapon(int dmg, std::string name) : Weapon(dmg, name) {
}

int MagicalWeapon::attack(const Player& p, const Attack& a) const {
    return a.attack_pts(p, *this);
}

int MagicalWeapon::defense(const Player& p, const Attack& a) const {
    return a.defense_pts(p, *this);
}
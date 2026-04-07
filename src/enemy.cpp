#include "enemy.h"
#include "entity.h"
#include "utils.h"

Enemy::Enemy(std::string name, int r, int c, int hp) : 
    Entity(r, c, hp),
    name(name),
    attack(next_random(5, 15)),
    armor(5),
    max_hp(hp)
    {}

const std::string& Enemy::get_name() const {
    return name;
}

const int& Enemy::get_attack() const {
    return attack;
}

const int& Enemy::get_arrmor() const {
    return armor;
}

const int& Enemy::get_max_hp() const {
    return max_hp;
}

void Enemy::take_dmg(int dmg) {
    if(dmg <= 0) {
        return;
    }
    hp = std::max(0, hp - std::max(0, dmg - armor));
}
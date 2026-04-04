#include "enemy.h"
#include "entity.h"
#include "utils.h"

Enemy::Enemy(std::string name, int r, int c) : 
    Entity(r, c),
    name(name),
    attack(next_random(5, 15)),
    armor(5)
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
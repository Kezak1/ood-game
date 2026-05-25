#include "enemy.h"
#include "enemy_event_visitor.h"
#include "entity.h"
#include "event_bus.h"
#include <memory>

Enemy::Enemy(std::string name, int r, int c, int atk, int armor, int hp, std::string species, std::unique_ptr<EnemyEventVisitor> l) : 
    Entity(name, r, c, hp, hp),
    attack(atk),
    armor(armor),
    species(species),
    listener(std::move(l)) {
    EventBus::instance().subscribe(*listener);
}

Enemy::~Enemy() {
    if(listener) {
        EventBus::instance().unsubscribe(*listener);
    }
}

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

const std::string& Enemy::get_species() const {
    return species;
}

void Enemy::weaken() {
    attack = std::max(0, attack - 3);
    armor = std::max(0, armor - 1);
}

void Enemy::strengthen() {
    attack += 3;
    armor += 1;
}
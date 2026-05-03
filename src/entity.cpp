#include "entity.h"

Entity::Entity(std::string name, int r, int c, int hp) : name(name), r(r), c(c), hp(hp) {}

const std::string& Entity::get_name() const {
    return name;
}

const int& Entity::get_r() const {
    return r;
}

void Entity::set_r(int row) {
    r = row;
}

const int& Entity::get_c() const {
    return c;
}

void Entity::set_c(int col) {
    c = col;
}

const int& Entity::get_hp() const {
    return hp;
}

bool Entity::is_dead() const {
    return hp == 0;
}
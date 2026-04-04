#include "entity.h"

Entity::Entity(int r, int c) : r(r), c(c) {}

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
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include <string>

class Enemy : public Entity {
    std::string name;
    int attack;
    int armor;
public:
    Enemy(std::string name, int r, int c);

    const std::string& get_name() const; 
    const int& get_attack() const;
    const int& get_arrmor() const;
};  

#endif

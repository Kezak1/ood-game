#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#include <string>

class Enemy : public Entity {
    std::string name;
    int attack;
    int armor;
    int max_hp;
public:
    Enemy(std::string name, int r, int c, int atk, int hp);

    const std::string& get_name() const; 
    const int& get_attack() const;
    const int& get_arrmor() const;
    const int& get_max_hp() const;

    void take_dmg(int dmg);
};  

#endif

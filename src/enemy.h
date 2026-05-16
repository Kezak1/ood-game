#pragma once

#include "entity.h"
#include "logger.h"

#include <string>

class Enemy : public Entity {
    int attack;
    int armor;
    int max_hp;
    std::string species;
public:
    Enemy(std::string name, int r, int c, int atk, int armor, int hp, std::string species = "");

    const std::string& get_name() const; 
    const int& get_attack() const;
    const int& get_arrmor() const;
    const int& get_max_hp() const;
    const std::string& get_species() const;

    void take_dmg(int dmg);
    void weaken();
    void strengthen();
};  

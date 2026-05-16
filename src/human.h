#pragma once

#include "enemy.h"

class Human : public Enemy {
public:
    static constexpr auto SPECIES = "human";
    Human(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger);
};

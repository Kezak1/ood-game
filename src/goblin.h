#pragma once

#include "enemy.h"
#include "enemy_event_visitor.h"
#include "event.h"
#include "null_event_visitor.h"

class Goblin;

class GoblinEventVisitor : public EnemyEventVisitor {
public:
    GoblinEventVisitor(Goblin& g, Logger& logger);
    void visit(const EnemyDefeatEvent&) override;
};

class Goblin : public Enemy {
    GoblinEventVisitor listener;
public:
    static constexpr auto SPECIES = "goblin";

    Goblin(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger);
    ~Goblin();
};

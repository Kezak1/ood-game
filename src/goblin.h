#pragma once

#include "enemy.h"
#include "event.h"
#include "null_event_visitor.h"

class Goblin;

class GoblinListener : public NullEventVisitor {
    Goblin& owner;
public:
    GoblinListener(Goblin& g);
    void visit(const SoundEvent&) override;
    void visit(const EnemyDefeatEvent&) override;
};

class Goblin : public Enemy {
    GoblinListener listener;
public:
    static constexpr auto SPECIES = "goblin";

    Goblin(std::string name, int r, int c, int atk, int armor, int hp);
    ~Goblin();
};

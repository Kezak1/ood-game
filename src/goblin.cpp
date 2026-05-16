#include "goblin.h"
#include "enemy.h"
#include "enemy_event_visitor.h"
#include "event.h"

GoblinEventVisitor::GoblinEventVisitor(Goblin& g, Logger& logger) : EnemyEventVisitor(g, logger) {}

void GoblinEventVisitor::visit(const SoundEvent& e) {
    EnemyEventVisitor::visit(e);
}

void GoblinEventVisitor::visit(const EnemyDefeatEvent& e) {
    if(e.species == Goblin::SPECIES) {
        owner.weaken();
    }
}


Goblin::Goblin(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger) 
    : Enemy(name, r, c, atk, armor, hp, SPECIES, std::make_unique<GoblinEventVisitor>(*this, logger)) {}
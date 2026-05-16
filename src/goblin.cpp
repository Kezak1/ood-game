#include "goblin.h"
#include "enemy.h"
#include "enemy_event_visitor.h"
#include "event.h"
#include "event_bus.h"
// #include "utils.h"

// GoblinEventVisitor::GoblinEventVisitor(Goblin& g, Logger& logger) : EnemyEventVisitor(g, logger) {}

// void GoblinEventVisitor::visit(const EnemyDefeatEvent& e) {
//     if(e.species == Goblin::SPECIES) {
//         owner.weaken();
//     }
// }


// Goblin::Goblin(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger) 
//     : Enemy(name, r, c, atk, armor, hp, SPECIES, logger), listener(*this) {
//     EventBus::instance().subscribe(listener);
// }

// Goblin::~Goblin() {
//     EventBus::instance().unsubscribe(listener);
// }

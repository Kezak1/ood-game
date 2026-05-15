#include "goblin.h"
#include "enemy.h"
#include "event.h"
#include "event_bus.h"
#include "utils.h"

GoblinListener::GoblinListener(Goblin& g) : owner(g) {}

void GoblinListener::visit(const EnemyDefeatEvent& e) {
    if(e.species == Goblin::SPECIES) {
        owner.weaken();
    }
}

void GoblinListener::visit(const SoundEvent& e) {
    int dis = walkable_dis(e.board, e.source_r, e.source_c, owner.get_r(), owner.get_c());
    if(dis >= 0 && dis <= e.range) {
        // logging
    }
}


Goblin::Goblin(std::string name, int r, int c, int atk, int armor, int hp) 
    : Enemy(name, r, c, atk, armor, hp, SPECIES), listener(*this) {
    EventBus::instance().subscribe(listener);
}

Goblin::~Goblin() {
    EventBus::instance().unsubscribe(listener);
}

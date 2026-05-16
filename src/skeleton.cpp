#include "skeleton.h"
#include "enemy.h"
#include "event.h"
#include "event_bus.h"
#include "utils.h"

SkeletonListener::SkeletonListener(Skeleton& s) : owner(s) {}

void SkeletonListener::visit(const EnemyDefeatEvent& e) {
    if(e.species == Skeleton::SPECIES) {
        owner.strengthen();
    }
}

void SkeletonListener::visit(const SoundEvent& e) {
    int dis = walkable_dis(e.board, e.source_r, e.source_c, owner.get_r(), owner.get_c());
    if(dis >= 0 && dis <= e.range) {
        // logging
    }
}


Skeleton::Skeleton(std::string name, int r, int c, int atk, int armor, int hp)
    : Enemy(name, r, c, atk, armor, hp, SPECIES), listener(*this) {
    EventBus::instance().subscribe(listener);
}

Skeleton::~Skeleton() {
    EventBus::instance().unsubscribe(listener);
}

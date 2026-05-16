#include "skeleton.h"
#include "enemy.h"
#include "enemy_event_visitor.h"
#include "event.h"
#include "logger.h"

SkeletonEnemyVisitor::SkeletonEnemyVisitor(Skeleton& s, Logger& logger) 
    : EnemyEventVisitor(s, logger) {}

void SkeletonEnemyVisitor::visit(const SoundEvent& e) {
    EnemyEventVisitor::visit(e);
}

void SkeletonEnemyVisitor::visit(const EnemyDefeatEvent& e) {
    if(e.species == Skeleton::SPECIES) {
        owner.strengthen();
    }
}

Skeleton::Skeleton(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger)
    : Enemy(name, r, c, atk, armor, hp, SPECIES, std::make_unique<SkeletonEnemyVisitor>(*this, logger)) {}
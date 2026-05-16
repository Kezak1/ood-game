#pragma once

#include "enemy.h"
#include "enemy_event_visitor.h"
#include "event.h"
#include "logger.h"
#include "null_event_visitor.h"

class Skeleton;

class SkeletonEnemyVisitor : public EnemyEventVisitor {
public:
    SkeletonEnemyVisitor(Skeleton&, Logger& logger);
    void visit(const SoundEvent&) override;
    void visit(const EnemyDefeatEvent&) override;
};


class Skeleton : public Enemy {
public:
    static constexpr auto SPECIES = "skeleton";

    Skeleton(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger);
};
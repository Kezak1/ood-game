#pragma once

#include "enemy.h"
#include "null_event_visitor.h"

class Skeleton;

class SkeletonListener : public NullEventVisitor {
    Skeleton& owner;
public:
    SkeletonListener(Skeleton&);
    void visit(const SoundEvent&) override;
    void visit(const EnemyDefeatEvent&) override;
};


class Skeleton : public Enemy {
    SkeletonListener listener;
public:
    static constexpr auto SPECIES = "skeleton";

    Skeleton(std::string name, int r, int c, int atk, int armor, int hp);
    ~Skeleton();
};
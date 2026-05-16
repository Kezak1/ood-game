#pragma once

#include "enemy.h"
#include "logger.h"
#include "null_event_visitor.h"

class EnemyEventVisitor : public NullEventVisitor {
    Enemy& owner;
    Logger& logger;
public:
    EnemyEventVisitor(Enemy&, Logger&);
    void visit(const SoundEvent&) override;
};

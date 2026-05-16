#pragma once

#include "logger.h"
#include "null_event_visitor.h"

class Enemy;

class EnemyEventVisitor : public NullEventVisitor {
protected:
    Enemy& owner;
    Logger& logger;
public:
    EnemyEventVisitor(Enemy&, Logger&);
    void visit(const SoundEvent&) override;
};

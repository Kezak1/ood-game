#pragma once

#include "event.h"

class NullEventVisitor : public EventVisitor {
public:
    void visit(const PlayerMoveEvent&) override {};
    void visit(const WallHitEvent&) override {};
    void visit(const ItemPickUpEvent&) override {};
    void visit(const ItemDropEvent&) override {};
    void visit(const ItemEquipEvent&) override {};
    void visit(const ItemUnequipEvent&) override {};
    void visit(const BattleStartEvent&) override {};
    void visit(const AttackEvent&) override {};
    void visit(const EnemyDefeatEvent&) override {};
    void visit(const PlayerDefeatEvent&) override {};
    void visit(const UnknownKeyEvent&) override {};
    void visit(const SoundEvent&) override {};
};

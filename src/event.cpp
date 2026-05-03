#include "event.h"

PlayerMoveEvent::PlayerMoveEvent(std::string direction) : direction(direction) {}

void PlayerMoveEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

WallHitEvent::WallHitEvent(std::string direction) : direction(direction) {}

void WallHitEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemPickUpEvent::ItemPickUpEvent(std::string item_name) : item_name(item_name) {}

void ItemPickUpEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemDropEvent::ItemDropEvent(std::string item_name) : item_name(item_name) {}

void ItemDropEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemEquipEvent::ItemEquipEvent(std::string item_name) : item_name(item_name) {}

void ItemEquipEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemUnequipEvent::ItemUnequipEvent(std::string item_name) : item_name(item_name) {}

void ItemUnequipEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

BattleStartEvent::BattleStartEvent(std::string enemy_name) : enemy_name(enemy_name) {}

void BattleStartEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

AttackEvent::AttackEvent(std::string attacker, std::string target, int dmg) : attacker(attacker), target(target), dmg(dmg) {}

void AttackEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

EnemyDefeatEvent::EnemyDefeatEvent(std::string enemy_name) : enemy_name(enemy_name) {}

void EnemyDefeatEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

PlayerDefeatEvent::PlayerDefeatEvent(std::string enemy_name) : enemy_name(enemy_name) {}

void PlayerDefeatEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

UnknownKeyEvent::UnknownKeyEvent(char key) : key(key) {}

void UnknownKeyEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

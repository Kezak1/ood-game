#include "event.h"

PlayerMoveEvent::PlayerMoveEvent(std::string player_name, std::string direction) : player_name(player_name), direction(direction) {}

void PlayerMoveEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

WallHitEvent::WallHitEvent(std::string player_name, std::string direction) : player_name(player_name), direction(direction) {}

void WallHitEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

PlayerCollisionEvent::PlayerCollisionEvent(std::string player_name) : player_name(player_name) {}

void PlayerCollisionEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemPickUpEvent::ItemPickUpEvent(std::string player_name, std::string item_name) : player_name(player_name), item_name(item_name) {}

void ItemPickUpEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemDropEvent::ItemDropEvent(std::string player_name, std::string item_name) : player_name(player_name), item_name(item_name) {}

void ItemDropEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemEquipEvent::ItemEquipEvent(std::string player_name, std::string item_name) : player_name(player_name), item_name(item_name) {}

void ItemEquipEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ItemUnequipEvent::ItemUnequipEvent(std::string player_name, std::string item_name) : player_name(player_name), item_name(item_name) {}

void ItemUnequipEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

BattleStartEvent::BattleStartEvent(std::string player_name, std::string enemy_name) : player_name(player_name), enemy_name(enemy_name) {}

void BattleStartEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

AttackEvent::AttackEvent(std::string attacker, std::string target, int dmg) : attacker(attacker), target(target), dmg(dmg) {}

void AttackEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

EnemyDefeatEvent::EnemyDefeatEvent(std::string player_name, std::string enemy_name, std::string species) : player_name(player_name), enemy_name(enemy_name), species(species) {}

void EnemyDefeatEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

PlayerDefeatEvent::PlayerDefeatEvent(std::string player_name, std::string enemy_name) : player_name(player_name), enemy_name(enemy_name) {}

void PlayerDefeatEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

UnknownKeyEvent::UnknownKeyEvent(char key) : key(key) {}

void UnknownKeyEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

SoundEvent::SoundEvent(int source_r, int source_c, int range, const std::vector<std::vector<Cell>>& board) 
    : source_r(source_r), source_c(source_c), range(range), board(board) {}

void SoundEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}

ActionFailedEvent::ActionFailedEvent(std::string reason) : reason(reason) {
}

void ActionFailedEvent::accept(EventVisitor& visitor) const {
    visitor.visit(*this);
}
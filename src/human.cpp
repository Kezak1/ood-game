#include "human.h"
#include "enemy_event_visitor.h"

Human::Human(std::string name, int r, int c, int atk, int armor, int hp, Logger& logger)
    : Enemy(name, r, c, atk, armor, hp, SPECIES, std::make_unique<EnemyEventVisitor>(*this, logger)) {}

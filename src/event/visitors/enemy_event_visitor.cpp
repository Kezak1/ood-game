#include "enemy_event_visitor.h"
#include "enemy.h"
#include "event.h"
#include "logger.h"
#include "utils.h"


EnemyEventVisitor::EnemyEventVisitor(Enemy& owner, Logger& logger)
    : owner(owner), logger(logger) {}

void EnemyEventVisitor::visit(const SoundEvent& e) {
    int dis = walkable_dis(e.board, e.source_r, e.source_c, owner.get_r(), owner.get_c());
    if(dis >= 0 && dis <= e.range) {
        logger.log(std::format("{} at ({}, {}) heard sound from ({}, {}) at distance {}", 
            owner.get_name(), owner.get_r(), owner.get_c(), e.source_r, e.source_c, dis));
    }
}
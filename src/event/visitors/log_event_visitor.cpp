#include "log_event_visitor.h"
#include "event.h"

#include <cctype>
#include <format>
#include <string>

std::string printable_key(char key) {
    auto c = (unsigned char)key;

    switch(key) {
        case '\0':
            return "\\0";
        case '\a':
            return "\\a";
        case '\b':
            return "\\b";
        case '\t':
            return "\\t";
        case '\n':
            return "\\n";
        case '\v':
            return "\\v";
        case '\f':
            return "\\f";
        case '\r':
            return "\\r";
        case '\'':
            return "\\'";
        case '\\':
            return "\\\\";
        default:
            if(std::isprint(c)) {
                return std::string(1, key);
            }
            return std::format("\\x{:02X}", (int)c);
    }
}

LogEventVisitor::LogEventVisitor(Logger& logger) : logger(logger) {}

void LogEventVisitor::visit(const PlayerMoveEvent& e) {
    logger.log(e.player_name + " moved " + e.direction);
}

void LogEventVisitor::visit(const WallHitEvent& e) {
    logger.log(e.player_name + " tried to walk into wall while moving " + e.direction);
}

void LogEventVisitor::visit(const PlayerCollisionEvent& e) {
    logger.log(e.player_name + " collided with other player");
}

void LogEventVisitor::visit(const ItemPickUpEvent& e) {
    logger.log(e.player_name + " picked up " + e.item_name);
}

void LogEventVisitor::visit(const ItemDropEvent& e) {
    logger.log(e.player_name + " dropped " + e.item_name);
}

void LogEventVisitor::visit(const ItemEquipEvent& e) {
    logger.log(e.player_name + " equipped " + e.item_name);
}

void LogEventVisitor::visit(const ItemUnequipEvent& e) {
    logger.log(e.player_name + " unequipped " + e.item_name);
}

void LogEventVisitor::visit(const BattleStartEvent& e) {
    logger.log(e.player_name + " started battle with " + e.enemy_name);
}

void LogEventVisitor::visit(const AttackEvent& e) {
    logger.log(std::format("{} attacked {} and dealth {} damage", e.attacker, e.target, e.dmg));
}

void LogEventVisitor::visit(const EnemyDefeatEvent& e) {
    logger.log(e.player_name + " defeated " + e.enemy_name);
}

void LogEventVisitor::visit(const PlayerDefeatEvent& e) {
    logger.log(e.player_name + " was defeated by " + e.enemy_name);
}

void LogEventVisitor::visit(const UnknownKeyEvent& e) {
    logger.log(std::format("You pressed unknown key '{}'", printable_key(e.key)));
}

void LogEventVisitor::visit(const SoundEvent& e) {
    logger.log(std::format("Sound made at ({}, {}) range={}", e.source_r, e.source_c, e.range));
}

void LogEventVisitor::visit(const ActionFailedEvent& e) {
    logger.log("Error: " + e.reason);
}

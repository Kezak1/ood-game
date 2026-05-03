#include "log_event_visitor.h"

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
    logger.log("Player moved " + e.direction);
}

void LogEventVisitor::visit(const WallHitEvent& e) {
    logger.log("Player tried to walk into wall while moving " + e.direction);
}

void LogEventVisitor::visit(const ItemPickUpEvent& e) {
    logger.log("Player picked up " + e.item_name);
}

void LogEventVisitor::visit(const ItemDropEvent& e) {
    logger.log("Player dropped " + e.item_name);
}

void LogEventVisitor::visit(const ItemEquipEvent& e) {
    logger.log("Player equipped " + e.item_name);
}

void LogEventVisitor::visit(const ItemUnequipEvent& e) {
    logger.log("Player unequipped" + e.item_name);
}

void LogEventVisitor::visit(const BattleStartEvent& e) {
    logger.log("Player started battle with " + e.enemy_name);
}

void LogEventVisitor::visit(const AttackEvent& e) {
    logger.log(std::format("{} attacked {} and dealth {} damage", e.attacker, e.target, e.dmg));
}

void LogEventVisitor::visit(const EnemyDefeatEvent& e) {
    logger.log("Player defeated " + e.enemy_name);
}

void LogEventVisitor::visit(const PlayerDefeatEvent& e) {
    logger.log("Player was defeated by " + e.enemy_name);
}

void LogEventVisitor::visit(const UnknownKeyEvent& e) {
    logger.log(std::format("Player pressed unknown key '{}'", printable_key(e.key)));
}

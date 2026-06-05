#pragma once

#include <string>
#include <vector>

#include "cell.h"

struct PlayerMoveEvent;
struct WallHitEvent;
struct PlayerCollisionEvent;
struct ItemPickUpEvent;
struct ItemDropEvent;
struct ItemEquipEvent;
struct ItemUnequipEvent;
struct BattleStartEvent;
struct AttackEvent;
struct EnemyDefeatEvent;
struct PlayerDefeatEvent;
struct UnknownKeyEvent;
struct SoundEvent;
struct ActionFailedEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visit(const PlayerMoveEvent&) = 0;
    virtual void visit(const WallHitEvent&) = 0;
    virtual void visit(const PlayerCollisionEvent&) = 0;
    virtual void visit(const ItemPickUpEvent&) = 0;
    virtual void visit(const ItemDropEvent&) = 0;
    virtual void visit(const ItemEquipEvent&) = 0;
    virtual void visit(const ItemUnequipEvent&) = 0;
    virtual void visit(const BattleStartEvent&) = 0;
    virtual void visit(const AttackEvent&) = 0;
    virtual void visit(const EnemyDefeatEvent&) = 0;
    virtual void visit(const PlayerDefeatEvent&) = 0;
    virtual void visit(const UnknownKeyEvent&) = 0;
    virtual void visit(const SoundEvent&) = 0;
    virtual void visit(const ActionFailedEvent&) = 0;
};

class Event {
public:
    virtual ~Event() = default;
    virtual void accept(EventVisitor&) const = 0;
};

struct PlayerMoveEvent : public Event { 
    std::string player_name;
    std::string direction;
    PlayerMoveEvent(std::string player_name, std::string direction);
    void accept(EventVisitor&) const override;
};

struct WallHitEvent : public Event {
    std::string player_name;
    std::string direction;
    WallHitEvent(std::string player_name, std::string direction);
    void accept(EventVisitor&) const override;
};

struct PlayerCollisionEvent : public Event {
    std::string player_name;
    PlayerCollisionEvent(std::string player_name);
    void accept(EventVisitor&) const override;
};

struct ItemPickUpEvent : public Event {
    std::string player_name;
    std::string item_name;
    ItemPickUpEvent(std::string player_name, std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemDropEvent : public Event {
    std::string player_name;
    std::string item_name;
    ItemDropEvent(std::string player_name, std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemEquipEvent : public Event {
    std::string player_name;
    std::string item_name;
    ItemEquipEvent(std::string player_name, std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemUnequipEvent : public Event {
    std::string player_name;
    std::string item_name;
    ItemUnequipEvent(std::string player_name, std::string item_name);
    void accept(EventVisitor&) const override;
};

struct BattleStartEvent : public Event {
    std::string player_name;
    std::string enemy_name;
    BattleStartEvent(std::string player_name, std::string enemy_name);
    void accept(EventVisitor&) const override;
};

struct AttackEvent : public Event {
    std::string attacker;
    std::string target;
    int dmg;

    AttackEvent(std::string attacker, std::string target, int dmg);
    void accept(EventVisitor&) const override;
};

struct EnemyDefeatEvent : public Event {
    std::string player_name;
    std::string enemy_name;
    std::string species;
    EnemyDefeatEvent(std::string player_name, std::string enemy_name, std::string species);
    void accept(EventVisitor&) const override;
};

struct PlayerDefeatEvent : public Event {
    std::string player_name;
    std::string enemy_name;
    PlayerDefeatEvent(std::string player_name, std::string enemy_name);
    void accept(EventVisitor&) const override;
};

struct UnknownKeyEvent : public Event {
    char key;
    UnknownKeyEvent(char key);
    void accept(EventVisitor&) const override;
};

struct SoundEvent : public Event {
    int source_r, source_c;
    int range;
    const std::vector<std::vector<Cell>>& board;
    SoundEvent(int source_r, int source_c, int range, const std::vector<std::vector<Cell>>& board);
    void accept(EventVisitor&) const override;
};

struct ActionFailedEvent : public Event {
    std::string reason;
    ActionFailedEvent(std::string reason);
    void accept(EventVisitor&) const override;
};

#ifndef EVENT_H
#define EVENT_H

#include <string>

struct PlayerMoveEvent;
struct WallHitEvent;
struct ItemPickUpEvent;
struct ItemDropEvent;
struct ItemEquipEvent;
struct ItemUnequipEvent;
struct BattleStartEvent;
struct AttackEvent;
struct EnemyDefeatEvent;
struct PlayerDefeatEvent;
struct UnknownKeyEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visit(const PlayerMoveEvent&) = 0;
    virtual void visit(const WallHitEvent&) = 0;
    virtual void visit(const ItemPickUpEvent&) = 0;
    virtual void visit(const ItemDropEvent&) = 0;
    virtual void visit(const ItemEquipEvent&) = 0;
    virtual void visit(const ItemUnequipEvent&) = 0;
    virtual void visit(const BattleStartEvent&) = 0;
    virtual void visit(const AttackEvent&) = 0;
    virtual void visit(const EnemyDefeatEvent&) = 0;
    virtual void visit(const PlayerDefeatEvent&) = 0;
    virtual void visit(const UnknownKeyEvent&) = 0;
};

class Event {
public:
    virtual ~Event() = default;
    virtual void accept(EventVisitor&) const = 0;
};

struct PlayerMoveEvent : public Event { 
    std::string direction;
    PlayerMoveEvent(std::string direction);
    void accept(EventVisitor&) const override;
};

struct WallHitEvent : public Event {
    std::string direction;
    WallHitEvent(std::string direction);
    void accept(EventVisitor&) const override;
};

struct ItemPickUpEvent : public Event {
    std::string item_name;
    ItemPickUpEvent(std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemDropEvent : public Event {
    std::string item_name;
    ItemDropEvent(std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemEquipEvent : public Event {
    std::string item_name;
    ItemEquipEvent(std::string item_name);
    void accept(EventVisitor&) const override;
};

struct ItemUnequipEvent : public Event {
    std::string item_name;
    ItemUnequipEvent(std::string item_name);
    void accept(EventVisitor&) const override;
};

struct BattleStartEvent : public Event {
    std::string enemy_name;
    BattleStartEvent(std::string enemy_name);
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
    std::string enemy_name;
    EnemyDefeatEvent(std::string enemy_name);
    void accept(EventVisitor&) const override;
};

struct PlayerDefeatEvent : public Event {
    std::string enemy_name;
    PlayerDefeatEvent(std::string enemy_name);
    void accept(EventVisitor&) const override;
};

struct UnknownKeyEvent : public Event {
    char key;
    UnknownKeyEvent(char key);
    void accept(EventVisitor&) const override;
};

#endif

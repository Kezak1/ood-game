#pragma once

#include <memory>
#include <string>
#include <nlohmann/json.hpp>

class GameModel;

class Command {
public:
    virtual ~Command() = default;

    virtual void execute(GameModel& model, int player_id) const = 0;
    virtual nlohmann::json to_json() const = 0;
    static std::unique_ptr<Command> from_json(const nlohmann::json& j);
};


class MoveCommand : public Command {
    std::string direction;
public:
    explicit MoveCommand(std::string direction);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class PickUpCommand : public Command {
    int idx;
public:
    explicit PickUpCommand(int idx);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class DropCommand : public Command {
    int idx;
public:
    explicit DropCommand(int idx);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class EquipCommand : public Command {
    int idx;
public:
    explicit EquipCommand(int idx);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class UnequipCommand : public Command {
    std::string hand;
public:
    explicit UnequipCommand(std::string hand);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class BattleStartCommand : public Command {
public:
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class BattleRoundCommand : public Command {
    std::string hand;
    std::string attack;
public:
    BattleRoundCommand(std::string hand, std::string attack);
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};

class GiveUpCommand : public Command {
public:
    void execute(GameModel& model, int player_id) const override;
    nlohmann::json to_json() const override;
};
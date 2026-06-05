#include "command.h"
#include "event.h"
#include "event_bus.h"
#include "game_model.h"
#include "normal_attack.h"
#include "stealth_attack.h"
#include "magical_attack.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>

using nlohmann::json;

namespace {
    const Item* battle_item(const Player& p, const std::string& hand) {
        if(hand == "left") {
            return p.get_left_hand().get();
        } else if(hand == "right") {
            return p.get_right_hand().get();
        } else if(hand == "both") {
            return p.get_both_hands().get();
        }
        return nullptr;
    }

    std::unique_ptr<Attack> battle_attack(std::string attack_type) {
        if(attack_type == "normal") {
            return std::make_unique<NormalAttack>();
        }
        if(attack_type == "stealth") {
            return std::make_unique<StealthAttack>();
        }
        if(attack_type == "magical") {
            return std::make_unique<MagicalAttack>();
        }

        return nullptr;
    }
}

MoveCommand::MoveCommand(std::string direction) : direction(direction) {}

void MoveCommand::execute(GameModel& model, int player_id) const {
    model.player_try_move(player_id, direction);
}

json MoveCommand::to_json() const {
    return {
        {"type", "move"}, 
        {"direction", direction}
    };
}

PickUpCommand::PickUpCommand(int idx) : idx(idx) {}

void PickUpCommand::execute(GameModel& model, int player_id) const {
    model.player_try_pick_up_item(player_id, idx);
}

json PickUpCommand::to_json() const {
    return {
        {"type", "pick_up"},
        {"idx", idx}
    };
}

DropCommand::DropCommand(int idx) : idx(idx) {}

void DropCommand::execute(GameModel& model, int player_id) const {
    model.player_try_drop_item(player_id, idx);
}

json DropCommand::to_json() const {
    return {
        {"type", "drop"},
        {"idx", idx}  
    };
}

EquipCommand::EquipCommand(int idx) : idx(idx) {}

void EquipCommand::execute(GameModel& model, int player_id) const {
    model.player_try_equip_item(player_id, idx);
}

json EquipCommand::to_json() const {
    return {
        {"type", "equip"},
        {"idx", idx}
    };
}

UnequipCommand::UnequipCommand(std::string hand) : hand(hand) {}

void UnequipCommand::execute(GameModel& model, int player_id) const {
    model.player_try_unequip_item(player_id, hand);
}

json UnequipCommand::to_json() const {
    return {
        {"type", "unequip"},
        {"hand", hand}
    };
}

void BattleStartCommand::execute(GameModel& model, int player_id) const {
    model.player_try_start_battle(player_id);
}

json BattleStartCommand::to_json() const {
    return {
        {"type", "battle_start"}
    };
}

BattleRoundCommand::BattleRoundCommand(std::string hand, std::string attack) :
    hand(hand), attack(attack) {}

void BattleRoundCommand::execute(GameModel& model, int player_id) const {
    const auto& p = model.player(player_id);
    const Item* item = battle_item(p, hand);
    std::unique_ptr<Attack> atk = battle_attack(attack);
    
    if(!item || !atk) {
        EventBus::instance().publish(ActionFailedEvent("invalid hand or attack"));
        return;
    }
    model.battle_round(player_id, *item, *atk);
}

json BattleRoundCommand::to_json() const {
    return {
        {"type", "battle_round"},
        {"hand", hand},
        {"attack", attack}
    };
}

void GiveUpCommand::execute(GameModel& model, int player_id) const {
    model.player_give_up(player_id);
}

json GiveUpCommand::to_json() const {
    return {{"type", "give_up"}};
}


std::unique_ptr<Command> Command::from_json(const json& j) {
    std::string type = j.at("type");

    if(type == "move") {
        return std::make_unique<MoveCommand>(j.at("direction"));
    }
    if(type == "pick_up") {
        return std::make_unique<PickUpCommand>(j.at("idx"));
    }
    if(type == "drop") {
        return std::make_unique<DropCommand>(j.at("idx"));
    }
    if(type == "equip") {
        return std::make_unique<EquipCommand>(j.at("idx"));
    }
    if(type == "unequip") {
        return std::make_unique<UnequipCommand>(j.at("hand"));
    }
    if(type == "battle_start") {
        return std::make_unique<BattleStartCommand>();
    }
    if(type == "battle_round") {
        return std::make_unique<BattleRoundCommand>(j.at("hand"), j.at("attack"));
    }
    if(type == "give_up") {
        return std::make_unique<GiveUpCommand>();
    }

    throw std::runtime_error("json, unknown command type: " + type);
}

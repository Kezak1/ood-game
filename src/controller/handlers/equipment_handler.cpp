#include "equipment_handler.h"
#include "action_handler.h"
#include "command.h"
#include "event_bus.h"
#include "event.h"
#include "view.h"

#include <exception>
#include <memory>

HandleResult EquipmentHandler::handle(const GameModel& model, int player_id, View& view, char key) {
    switch(tolower(key)) {
        case 'k': {
            if(model.player(player_id).get_inventory().empty()) {
                return {true};
            }

            std::string input = view.ask("Enter index of item from inventory (to cancel write 'cancel'): ");
            if(input == "cancel") {
                return {true};
            }

            int idx = -1;
            try {
                idx = std::stoi(input);
            } catch(const std::exception&) {
                EventBus::instance().publish(ActionFailedEvent("invalid number"));
                return {true};
            }

            return {true, std::make_unique<EquipCommand>(idx)};
        }
        case 'l': {
            auto& p = model.player(player_id);
            if(!p.get_left_hand() && !p.get_right_hand() && !p.get_both_hands()) {
                return {true};
            }
            std::string input = view.ask("Enter 'left'/'right'/'both' to unequip (to cancel write 'cancel'): ");
            if(input == "cancel") {
                return {true};
            }

            return {true, std::make_unique<UnequipCommand>(input)};
        }
        default:
            return {};
    }
}
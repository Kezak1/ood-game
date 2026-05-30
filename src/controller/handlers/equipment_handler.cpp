#include "equipment_handler.h"
#include "event_bus.h"
#include "event.h"
#include "game_model.h"
#include "player.h"
#include "view.h"

#include <exception>

std::optional<bool> EquipmentHandler::handle(GameModel& model, View& view, char key) {
    switch(tolower(key)) {
        case 'k': {
            if(model.player().get_inventory().empty()) {
                return false;
            }

            std::string input = view.ask("Enter index of item from inventory (to cancel write 'cancel'): ");
            if(input == "cancel") {
                return false;
            }

            int idx = -1;
            try {
                idx = std::stoi(input);
            } catch(const std::exception&) {
                EventBus::instance().publish(ActionFailedEvent("invalid number"));
                return false;
            }

            model.player_try_equip_weapon(idx);

            return false;
        }
        case 'l': {
            std::string input = view.ask("Enter 'left'/'right'/'both' to unequip (to cancel write 'cancel'): ");
            if(input == "cancel") {
                return false;
            }

            model.player_try_unequip_weapon(input);

            return false;
        }
        default:
            return std::nullopt;
    }
}
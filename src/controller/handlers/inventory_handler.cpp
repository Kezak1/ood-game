#include "inventory_handler.h"
#include "event.h"
#include "game_model.h"
#include "view.h"
#include "event_bus.h"

#include <exception>
#include <optional>
#include <sstream>

namespace {
    void try_get_item_info(Player& p, View& view) {
        if (p.get_inventory().empty() && !p.get_both_hands() && !p.get_left_hand() && !p.get_right_hand()) {
            return;
        }

        std::string input = view.ask("Enter inventory index or 'left'/'right'/'both' to get info about chosen item (to cancel write 'cancel'): ");

        if(input == "cancel") {
            return;
        }

        try {
            std::stringstream ss;
            ss << "INFO: ";

            if(input == "left") {
                ss << p.get_left_hand_info();
            } else if(input == "right") {
                ss << p.get_right_hand_info();
            } else if(input == "both") {
                ss << p.get_both_hand_info();
            } else {
                int idx = std::stoi(input);
                ss << p.get_item_info(idx);
            }
            ss << '\n';

            view.tell(ss.str());
        } catch(const std::exception& e) {
            EventBus::instance().publish(ActionFailedEvent(e.what()));
        }
    }

    std::optional<int> get_idx(View& view, const std::string& question) {
        std::string input = view.ask(question);
        if(input == "cancel") {
            return std::nullopt;
        }

        int idx;
        try {
            idx = std::stoi(input);
        } catch(const std::exception& e) {
            EventBus::instance().publish(ActionFailedEvent("invalid number"));
            return std::nullopt;
        }

        return idx;
    }
}

std::optional<bool> InventoryHandler::handle(GameModel& model, View& view, char key) {
    switch(tolower(key)) {
        case 'e': {
            auto idx = get_idx(view, "Enter index which item to pick up (to cancel write 'cancel'): ");
            if(idx == std::nullopt) {
                return false;
            }
            model.player_try_pick_up_item(*idx);
            return false;
        }
        case 'g': {
            auto idx = get_idx(view, "Enter index of item to drop it from inventory (to cancel write 'cancel'): ");
            if(idx == std::nullopt) {
                return false;
            }
            model.player_try_drop_item(*idx);
            return false;
        }
        case 'i':
            try_get_item_info(model.player(), view);
            return false;
        default:
            return std::nullopt;
    }
}
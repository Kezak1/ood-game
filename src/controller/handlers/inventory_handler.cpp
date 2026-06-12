#include "inventory_handler.h"
#include "action_handler.h"
#include "command.h"
#include "event.h"
#include "view.h"
#include "event_bus.h"

#include <exception>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>

namespace {
    void try_get_item_info(View& view, const Player& p) {
        if (p.get_inventory().empty() && !p.get_both_hands() && !p.get_left_hand() && !p.get_right_hand()) {
            return;
        }

        std::string input = view.ask("Enter inventory index or 'left'/'right'/'both' to get info (to cancel write 'cancel'): ");

        if(input == "cancel") {
            return;
        }

        try {
            std::stringstream ss;
            ss << "INFO: ";

            if(input == "left") {
                ss << p.get_left_hand()->get_info();
            } else if(input == "right") {
                ss << p.get_right_hand()->get_info();
            } else if(input == "both") {
                ss << p.get_both_hands()->get_info();
            } else {
                int idx = std::stoi(input);
                if(idx < 1 || idx > (int)p.get_inventory().size()) {
                    throw std::out_of_range("invalid idx");
                }
                ss << p.get_inventory()[idx - 1]->get_info();
            }
            
            view.tell(ss.str());
            view.wait_any_key();
        } catch(const std::exception& e) {
            EventBus::instance().publish(ActionFailedEvent(e.what()));
        }
    }

    std::optional<int> get_idx(View& view, const std::string& question) {
        std::string input = view.ask(question);
        if(input == "cancel") {
            return std::nullopt;
        }

        try {
            return std::stoi(input);
        } catch(const std::exception& e) {
            EventBus::instance().publish(ActionFailedEvent("invalid number"));
            return std::nullopt;
        }
    }
}

HandleResult InventoryHandler::handle(const GameModel& model, int player_id, View& view, char key) {
    const auto& p = model.player(player_id); 
    switch(tolower(key)) {
        case 'e': {
            if(model.cell_at(p.get_r(), p.get_c()).get_items().empty()) {
                return {true};
            }
            auto idx = get_idx(view, "Enter index which item to pick up (to cancel write 'cancel'): ");
            if(!idx) {
                return {true};
            }
            return {true, std::make_unique<PickUpCommand>(*idx)};
        }
        case 'g': {
            if(p.get_inventory().empty()) {
                return {true};
            }
            auto idx = get_idx(view, "Enter index of item to drop it from inventory (to cancel write 'cancel'): ");
            if(!idx) {
                return {true};
            }
            return {true, std::make_unique<DropCommand>(*idx)};
        }
        case 'i':
            try_get_item_info(view, model.player(player_id));
            return {true};
        default:
            return {};
    }
}
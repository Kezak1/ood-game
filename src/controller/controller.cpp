#include "controller.h"

#include "event.h"
#include "event_bus.h"
#include "game_model.h"
#include "quit_handler.h"
#include "move_handler.h"
#include "equipment_handler.h"
#include "inventory_handler.h"
#include "battle_handler.h"
#include "view_log_handler.h"
#include "command.h"

#include <cctype>

namespace {
    inline constexpr int LOCAL_ID = 1;

    std::string auto_choose_hand(const Player& p) {
        if(p.get_both_hands()) {
            return "both";
        }
        if(p.get_left_hand() && !p.get_right_hand()) {
            return "left";
        }
        if(!p.get_left_hand() && p.get_right_hand()) {
            return "right";
        }
        return "";
    }
}

Controller::Controller(GameModel& model, View& view, std::string player_name, std::filesystem::path log_path)
    : model(model), view(view), log_path(log_path) {
    model.add_player(LOCAL_ID, player_name);
    init_handlers();
}   

void Controller::loop() {
    view.clear();

    while(true) {
        view.render(model, LOCAL_ID);

        if(model.is_player_in_battle(LOCAL_ID)) {
            run_battle();
            if(model.player(LOCAL_ID).is_dead()) {
                break;
            }
            continue;
        }

        char k = std::tolower(view.read_key());

        HandleResult res;

        for(auto& h : handlers) {
            res = h->handle(model, LOCAL_ID, view, k);
            if(res.handled) {
                break;
            }
        }

        if(!res.handled) {
            EventBus::instance().publish(UnknownKeyEvent(k));
            continue;
        } else {
            if(res.cmd) {
                res.cmd->execute(model, LOCAL_ID);
            }
            if(res.quit) {
                break;
            }
        }

        if(model.player(LOCAL_ID).is_dead()) {
            break;
        }

        model.enemies_take_turn();
    }

    if(model.player(LOCAL_ID).is_dead()) {
        view.clear();
        view.tell("GAME OVER\nLOG FILE: " + log_path.string());
    }
}

void Controller::run_battle() {
    while(model.is_player_in_battle(LOCAL_ID)) {
        view.render(model, LOCAL_ID);

        std::string hand = auto_choose_hand(model.player(LOCAL_ID));
        if(hand.empty()) {
            hand = view.ask("Choose hand 'left'/'right'/'both' (or 'give up'): ");
            if(hand == "give up") {
                GiveUpCommand().execute(model, LOCAL_ID);
                break;
            }
        }

        std::string attack = view.ask("Choose attack 'normal'/'stealth'/'magical' (or 'give up'): ");
        if(attack == "give up") {
            GiveUpCommand().execute(model, LOCAL_ID);
            break;
        }

        BattleRoundCommand(hand, attack).execute(model, LOCAL_ID);
    }
}

void Controller::init_handlers() {
    handlers.clear();
    handlers.push_back(std::make_unique<QuitHandler>());
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<EquipmentHandler>());
    handlers.push_back(std::make_unique<InventoryHandler>());
    handlers.push_back(std::make_unique<BattleHandler>());
    handlers.push_back(std::make_unique<ViewLogHandler>());
}
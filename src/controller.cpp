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

Controller::Controller(GameModel& model, View& view, std::filesystem::path log_path)
    : model(model), view(view), log_path(log_path) {
    init_handlers();
}   

void Controller::loop() {
    view.render_state(model);

    while(1) {
        char k = std::tolower(view.read_key());

        bool handled = false;
        bool quit = false;

        for(auto& h : handlers) {
            if(auto res = h->handle(model, view, k)) {
                handled = true;
                quit = *res;
                break;
            }
        }

        if(quit) break;

        if(!handled) {
            EventBus::instance().publish(UnknownKeyEvent(k));
        }

        model.enemies_take_turn();
        view.render_state(model);
    }

    if(model.player().is_dead()) {
        view.clear();
        view.tell("GAME OVER\nLOG FILE: " + log_path.string());
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
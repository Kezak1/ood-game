#pragma once

#include "game_model.h"
#include "view.h"
#include "action_handler.h"

#include <filesystem>
#include <memory>
#include <vector>


class Controller {
    GameModel& model;  
    View& view;
    std::filesystem::path log_path;
    
    std::vector<std::unique_ptr<ActionHandler>> handlers;
public:
    Controller(GameModel& model, View& view, std::string player_name, std::filesystem::path log_path);
    void loop();
private:
    void init_handlers();
    void run_battle();
};

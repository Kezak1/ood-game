#pragma once

#include "dungeon_builder.h"
#include "game_model.h"
#include "logger.h"
#include "view.h"
#include "action_handler.h"

#include <filesystem>
#include <memory>
#include <vector>
#include <string>

class Controller {
    GameModel& model;  
    View& view;
    std::filesystem::path log_path;

    std::vector<std::unique_ptr<ActionHandler>> handlers;
public:
    Controller(GameModel& model, View& view, std::filesystem::path log_path);
    void loop();
private:
    void init_handlers();
    BuildResult init_dungeon();
};

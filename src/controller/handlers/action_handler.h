#pragma once

#include <memory>

#include "command.h"

class View;
class GameModel;

struct HandleResult {
    bool handled = false;
    std::unique_ptr<Command> cmd = nullptr;
    bool quit = false;
};

class ActionHandler {
public:
    virtual ~ActionHandler() = default;
    virtual HandleResult handle(const GameModel& model, int player_id, View& view, char key) = 0;
};


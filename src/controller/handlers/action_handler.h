#pragma once

#include <optional>

class GameModel;
class View;

class ActionHandler {
public:
    virtual ~ActionHandler() = default;
    virtual std::optional<bool> handle(GameModel& game, View& view, char key) = 0;
};


#pragma once

#include <optional>

class Game;

class ActionHandler {
public:
    virtual ~ActionHandler() = default;
    virtual std::optional<bool> handle(Game& game, char key) = 0;
};


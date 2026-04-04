#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include <optional>

class Game;

class ActionHandler {
public:
    virtual ~ActionHandler() = default;
    virtual std::optional<bool> handle(Game& game, char key) = 0;
};

#endif

#pragma once

#include "action_handler.h"

class MoveHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

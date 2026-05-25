#pragma once

#include "action_handler.h"
#include "game_model.h"

#include <optional>

class QuitHandler : public ActionHandler {
public:
    std::optional<bool> handle(GameModel& game, View& view, char key) override;
};

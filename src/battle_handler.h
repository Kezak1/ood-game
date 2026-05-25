#pragma once

#include "action_handler.h"

class BattleHandler : public ActionHandler {
public:
    std::optional<bool> handle(GameModel& model, View& view, char key) override;
};

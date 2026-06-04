#pragma once

#include "action_handler.h"

class BattleHandler : public ActionHandler {
public:
    HandleResult handle(const GameModel& model, int player_id, View& view, char key) override;
};

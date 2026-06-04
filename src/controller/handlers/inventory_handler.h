#pragma once

#include "action_handler.h"

class InventoryHandler : public ActionHandler {
public:
    HandleResult handle(const GameModel& model, int player_id, View& view, char key) override;
};

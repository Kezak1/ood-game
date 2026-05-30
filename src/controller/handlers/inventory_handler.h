#pragma once

#include "action_handler.h"

#include <optional>

class InventoryHandler : public ActionHandler {
public:
    std::optional<bool> handle(GameModel& model, View& view, char key) override;
};

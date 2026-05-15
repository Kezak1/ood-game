#pragma once

#include "action_handler.h"

#include <optional>

class InventoryHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

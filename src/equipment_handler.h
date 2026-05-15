#pragma once

#include "action_handler.h"

#include <optional>

class EquipmentHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

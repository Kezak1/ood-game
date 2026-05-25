#pragma once

#include "action_handler.h"

#include <optional>

class EquipmentHandler : public ActionHandler {
public:
    std::optional<bool> handle(GameModel& model, View& view, char key) override;
};

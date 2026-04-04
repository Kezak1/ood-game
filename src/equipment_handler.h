#ifndef EQUIPMENT_HANDLER_H
#define EQUIPMENT_HANDLER_H

#include "action_handler.h"

#include <optional>

class EquipmentHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

#endif
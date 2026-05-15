#pragma once

#include "action_handler.h"

#include <optional>

class QuitHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

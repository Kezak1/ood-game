#pragma once

#include "action_handler.h"

class BeginBattleHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

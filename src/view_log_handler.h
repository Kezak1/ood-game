#pragma once

#include "action_handler.h"

class ViewLogHandler : public ActionHandler {
public:
std::optional<bool> handle(GameModel& game, View& view, char key) override;
};


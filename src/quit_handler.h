#ifndef QUIT_HANDLER_H
#define QUIT_HANDLER_H

#include "action_handler.h"

#include <optional>

class QuitHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

#endif
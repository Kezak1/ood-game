#ifndef VIEW_LOG_HANDLER_H
#define VIEW_LOG_HANDLER_H

#include "action_handler.h"

class ViewLogHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};


#endif
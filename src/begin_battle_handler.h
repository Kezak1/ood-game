#ifndef BEGIN_BATTLE_HANDLER_H
#define BEGIN_BATTLE_HANDLER_H

#include "action_handler.h"

class BeginBattleHandler : public ActionHandler {
public:
    std::optional<bool> handle(Game& game, char key) override;
};

#endif
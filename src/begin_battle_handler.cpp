#include "begin_battle_handler.h"
#include "game.h"

std::optional<bool> BeginBattleHandler::handle(Game& game, char key) {
    key = tolower(key);
    if(key != 'f') {
        return std::nullopt;
    }
    
    return game.battle();
}
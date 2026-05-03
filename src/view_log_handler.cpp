#include "view_log_handler.h"
#include "game.h"


std::optional<bool> ViewLogHandler::handle(Game& game, char key) {
    key = tolower(key);
    if(key != 'j') {
        return std::nullopt;
    }

    game.show_full_log_history();

    return false;
}
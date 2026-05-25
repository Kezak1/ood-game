#include "view_log_handler.h"

#include "game_model.h"
#include "view.h"


std::optional<bool> ViewLogHandler::handle(GameModel&, View& view, char key) {
    key = tolower(key);
    if(key != 'j') {
        return std::nullopt;
    }

    view.show_full_log();

    return false;
}
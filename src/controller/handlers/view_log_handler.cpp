#include "view_log_handler.h"

#include "action_handler.h"
#include "game_model.h"
#include "view.h"

// TO DO fix the scroll problem with logging
HandleResult ViewLogHandler::handle(const GameModel&, int, View& view, char key) {
    key = tolower(key);
    if(key != 'j') {
        return {};
    }

    view.show_full_log();
    return {true};
}
#include "quit_handler.h"

#include "game_model.h"
#include "view.h"

std::optional<bool> QuitHandler::handle(GameModel&, View&, char key) {
    key = tolower(key);
    if(key != 'q') {
        return std::nullopt;
    }
    return true;
}
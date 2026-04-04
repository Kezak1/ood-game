#include "quit_handler.h"
#include "game.h"

std::optional<bool> QuitHandler::handle(Game&, char key) {
    key = tolower(key);
    if(key != 'q') {
        return std::nullopt;
    }
    return true;
}
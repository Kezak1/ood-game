#include "quit_handler.h"

#include "action_handler.h"
#include "game_model.h"
#include "view.h"

HandleResult QuitHandler::handle(const GameModel&, int, View&, char key) {
    key = tolower(key);
    if(key != 'q') {
        return {};
    }
    return {true, nullptr, true};
}
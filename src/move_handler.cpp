#include "move_handler.h"

#include "game_model.h"
#include "view.h"

std::optional<bool> MoveHandler::handle(GameModel& model, View& view, char key) {
    switch(tolower(key)) {
        case 'w': 
            model.player_move_up();
            return false;
        case 's':
            model.player_move_down();
            return false;
        case 'a':
            model.player_move_left();
            return false;
        case 'd':
            model.player_move_right();
            return false;
        default:
            return std::nullopt;
    }
}

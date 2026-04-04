#include "move_handler.h"
#include "game.h"

std::optional<bool> MoveHandler::handle(Game& game, char key) {
    switch(tolower(key)) {
        case 'w': 
            game.player_move_up();
            return false;
        case 's':
            game.player_move_down();
            return false;
        case 'a':
            game.player_move_left();
            return false;
        case 'd':
            game.player_move_right();
            return false;
        default:
            return std::nullopt;
    }
}

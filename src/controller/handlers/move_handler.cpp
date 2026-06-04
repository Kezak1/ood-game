#include "move_handler.h"

#include "action_handler.h"
#include "view.h"
#include "command.h"

#include <memory>

HandleResult MoveHandler::handle(const GameModel&, int, View&, char key) {
    switch(tolower(key)) {
        case 'w': 
            return {true, std::make_unique<MoveCommand>("up")};
        case 's':
            return {true, std::make_unique<MoveCommand>("down")};
        case 'a':
            return {true, std::make_unique<MoveCommand>("left")};
        case 'd':
            return {true, std::make_unique<MoveCommand>("right")};
        default:
            return {};
    }
}

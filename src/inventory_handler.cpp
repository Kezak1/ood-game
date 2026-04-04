#include "inventory_handler.h"
#include "game.h"


std::optional<bool> InventoryHandler::handle(Game& game, char key) {
    switch(tolower(key)) {
        case 'e':
            game.player_try_pick_up_item();
            return false;
        case 'g':
            game.player_try_drop_item();
            return false;
        case 'i':
            game.player_try_get_item_info();
            return false;
        default:
            return std::nullopt;
    }
}
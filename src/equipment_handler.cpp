#include "equipment_handler.h"
#include "game.h"

std::optional<bool> EquipmentHandler::handle(Game& game, char key) {
    switch(tolower(key)) {
        case 'j':
            game.player_try_equip_weapon();
            return false;
        case 'k':
            game.player_try_unequip_weapon();
            return false;
        default:
            return std::nullopt;
    }
}
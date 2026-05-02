#include "black_wand.h"
#include "magical_weapon.h"
#include "player.h"

BlackWand::BlackWand() : MagicalWeapon(40, "black wand") {
}

std::string BlackWand::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> BlackWand::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}

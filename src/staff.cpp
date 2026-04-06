#include "staff.h"
#include "attack.h"
#include "player.h"

Staff::Staff() : MagicalWeapon(30, "staff") {
}

std::string Staff::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> Staff::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}

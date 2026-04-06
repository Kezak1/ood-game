#include "dagger.h"
#include "player.h"

Dagger::Dagger() : LightWeapon(15, "dagger") {
}

std::string Dagger::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> Dagger::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}

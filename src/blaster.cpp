#include "blaster.h"
#include "light_weapon.h"
#include "player.h"

Blaster::Blaster() : LightWeapon(20, "blaster") {
}

std::string Blaster::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> Blaster::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}
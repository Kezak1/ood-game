#include "axe.h"
#include "player.h"
#include <memory>

Axe::Axe() : HeavyWeapon(20, "axe") {
}

std::string Axe::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> Axe::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}
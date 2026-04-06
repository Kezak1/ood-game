#include "great_sword.h"
#include "player.h"

GreatSword::GreatSword() : HeavyWeapon(25, "great sword") {
}

std::string GreatSword::get_info() const {
    std::stringstream res;
    res << "hold: both, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> GreatSword::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_both_hands(self)) {
        return nullptr;
    }
    return self;
}

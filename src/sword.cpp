#include "sword.h"
#include "player.h"

Sword::Sword(int _dmg, std::string s) : Weapon(_dmg, s) {
}

std::string Sword::get_info() const {
    std::stringstream res;
    res << "sword, hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> Sword::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}

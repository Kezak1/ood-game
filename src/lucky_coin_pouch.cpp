#include "lucky_coin_pouch.h"
#include "magical_weapon.h"
#include "player.h"

LuckyCoinPouch::LuckyCoinPouch() : MagicalWeapon(20, "lucky coin pouch") {}

std::string LuckyCoinPouch::get_info() const {
    std::stringstream res;
    res << "hold: single, dmg: " << dmg;
    return res.str();
}

std::unique_ptr<Item> LuckyCoinPouch::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_both_hands(self)) {
        return nullptr;
    }
    return self;
}
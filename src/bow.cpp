#include "bow.h"
#include "player.h"

Bow::Bow(int _dmg, std::string s) : Weapon(_dmg, s) {
}

std::string Bow::get_info() const {
    std::stringstream res;
    res << "bow, hold: both" << get_stats();
    return res.str();
}

std::unique_ptr<Item> Bow::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_both_hands(self)) {
        return nullptr;
    }
    return self;
}

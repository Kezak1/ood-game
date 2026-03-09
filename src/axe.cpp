#include "axe.h"
#include "player.h"
#include <memory>

Axe::Axe(int _dmg, std::string s) : Weapon(_dmg, s) {
}

std::string Axe::get_info() const {
    std::stringstream res;
    res << "axe, hold: single" << get_stats();
    return res.str();
}

std::unique_ptr<Item> Axe::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}
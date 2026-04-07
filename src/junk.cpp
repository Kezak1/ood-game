#include "junk.h"
#include "player.h"

Junk::Junk(std::string s) : Item(s) {
}

std::string Junk::get_info() const {
    return "non-weapon item";
}

std::unique_ptr<Item> Junk::equip(Player& p, std::unique_ptr<Item> self) {
    if(p.equip_in_single_hand(self)) {
        return nullptr;
    }
    return self;
}

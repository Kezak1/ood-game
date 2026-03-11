#include "item.h"
#include "player.h"

Item::Item(std::string s) : name(s) {
}

const std::string& Item::get_name() const {
    return name;
}

std::string Item::get_info() const {
    return "plain item";
}

bool Item::on_pick_up(Player&) const {
    return true;
}

std::unique_ptr<Item> Item::equip(Player&, std::unique_ptr<Item> self) {
    return self;
}
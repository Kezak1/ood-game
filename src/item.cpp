#include "item.h"
#include "player.h"
#include "attack.h"

Item::Item(std::string s) : name(s) {
}

std::string Item::get_name() const {
    return name;
}

std::string Item::get_info() const {
    return "this shouldn't be possible haha";
}

int Item::get_dmg() const {
    return 0;
}

int Item::get_str_bonus() const {
    return 0;
}

int Item::get_dex_bonus() const {
    return 0;
}

int Item::get_lck_bonus() const {
    return 0;
}

int Item::get_agr_bonus() const {
    return 0;
}

int Item::get_wis_bonus() const {
    return 0;
}

bool Item::goes_to_inv() const {
    return true;
}

bool Item::on_pick_up(Player&) const {
    return goes_to_inv();
}

std::unique_ptr<Item> Item::equip(Player&, std::unique_ptr<Item> self) {
    return self;
}

int Item::attack(const Player& p, const Attack& a) const {
    return accept_attack(p, a, *this);
}

int Item::defense(const Player& p, const Attack& a) const {
    return accept_defense(p, a, *this);
}

int Item::accept_attack(const Player& p, const Attack& a, const Item& stats) const {
    return a.visit_attack(p, stats, stats);
}

int Item::accept_defense(const Player& p, const Attack& a, const Item& stats) const {
    return a.visit_defense(p, stats, stats);
}
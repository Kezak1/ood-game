#include "item.h"
#include "player.h"
#include "attack.h"

Item::Item(std::string s) : name(s) {
}

std::string Item::get_name() const {
    return name;
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

bool Item::on_pick_up(Player&) const {
    return true;
}

std::unique_ptr<Item> Item::equip(Player&, std::unique_ptr<Item> self) {
    return self;
}

int Item::attack(const Player& p, const Attack& a) const {
    return attack_dispatched(p, a, *this);
}

int Item::defense(const Player& p, const Attack& a) const {
    return defense_dispatched(p, a, *this);
}

int Item::attack_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.attack_pts(p, stats, stats);
}

int Item::defense_dispatched(const Player& p, const Attack& a, const Item& stats) const {
    return a.defense_pts(p, stats, stats);
}
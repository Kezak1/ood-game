#include "item.h"
#include "enemy.h"
#include "player.h"
#include "attack.h"

#include <algorithm>

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
    return a.attack_dmg(p, *this);
}

int Item::defense(const Player& p, const Enemy& e, const Attack& a) const {
    return e.get_attack() * 0.5 * std::clamp(a.defense_ratio(p, *this), 0.0, 1.0);
}
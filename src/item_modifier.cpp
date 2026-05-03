#include "item_modifier.h"
#include "item.h"
#include <memory>

ItemModifier::ItemModifier(std::unique_ptr<Item> item, std::string name) 
    : Item(""), inner(std::move(item)), modifier_name(name) {
}

std::string ItemModifier::get_name() const {
    return inner->get_name() + "(" + modifier_name + ")";
}

std::string ItemModifier::get_info() const {
    return inner->get_info();
}

int ItemModifier::get_dmg() const {
    return inner->get_dmg();
}

int ItemModifier::get_str_bonus() const {
    return inner->get_str_bonus();
}

int ItemModifier::get_dex_bonus() const {
    return inner->get_dex_bonus();
}

int ItemModifier::get_lck_bonus() const {
    return inner->get_lck_bonus();
}

int ItemModifier::get_agr_bonus() const {
    return inner->get_agr_bonus();
}

int ItemModifier::get_wis_bonus() const {
    return inner->get_wis_bonus();
}

bool ItemModifier::on_pick_up(Player& p) const {
    return inner->on_pick_up(p);
}

std::unique_ptr<Item> ItemModifier::equip(Player& p, std::unique_ptr<Item> self) {
    return inner->equip(p, std::move(self));
}

int ItemModifier::accept_attack(const Player& p,  const Attack& a, const Item& stats) const {
    return inner->accept_attack(p, a, stats);
}

int ItemModifier::accept_defense(const Player& p, const Attack& a, const Item& stats) const {
    return inner->accept_defense(p, a, stats);
}
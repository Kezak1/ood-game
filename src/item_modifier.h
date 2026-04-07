#ifndef ITEM_MODIFIER_H
#define ITEM_MODIFIER_H

#include "item.h"

#include <memory>
#include <string>

class ItemModifier : public Item {
protected:
    std::unique_ptr<Item> inner;
    std::string modifier_name;

public:
    ItemModifier(std::unique_ptr<Item> item, std::string name);

    std::string get_name() const override;
    std::string get_info() const override;

    int get_dmg() const override;
    int get_str_bonus() const override;
    int get_dex_bonus() const override;
    int get_lck_bonus() const override;
    int get_agr_bonus() const override;
    int get_wis_bonus() const override;

    bool on_pick_up(Player& p) const override;
    std::unique_ptr<Item> equip(Player&, std::unique_ptr<Item> self) override;

    int attack(const Player& p, const Attack& a) const override;
    int defense(const Player& p, const Attack& a) const override;
};

#endif

#pragma once

#include "magical_weapon.h"

class LuckyCoinPouch : public MagicalWeapon {
public:
    LuckyCoinPouch();
    std::string type_label() const override;
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

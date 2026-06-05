#pragma once

#include "heavy_weapon.h"

class Axe : public HeavyWeapon {
public:
    Axe();
    std::string type_label() const override;
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

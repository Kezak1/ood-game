#ifndef AXE_H
#define AXE_H

#include "heavy_weapon.h"

class Axe : public HeavyWeapon {
public:
    Axe();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
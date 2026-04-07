#ifndef GREAT_SWORD_H
#define GREAT_SWORD_H

#include "heavy_weapon.h"

class GreatSword : public HeavyWeapon {
public:
    GreatSword();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif

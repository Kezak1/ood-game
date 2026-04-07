#ifndef DAGGER_H
#define DAGGER_H

#include "light_weapon.h"

class Dagger : public LightWeapon {
public:
    Dagger();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
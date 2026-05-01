#ifndef BLASTER_H
#define BLASTER_H

#include "attack.h"
#include "light_weapon.h"
#include <memory>

class Blaster : public LightWeapon {
public:
    Blaster();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
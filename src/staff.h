#ifndef STAFF_H
#define STAFF_H

#include "attack.h"
#include "magical_weapon.h"

class Staff : public MagicalWeapon {
public:
    Staff();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
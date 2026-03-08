#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"

class Sword : public Weapon {
public:
    Sword(int _dmg, std::string s);
    virtual std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
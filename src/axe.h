#ifndef AXE_H
#define AXE_H

#include "weapon.h"
#include <memory>

class Axe : public Weapon {
public:
    Axe(int _dmg, std::string s);
    virtual std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
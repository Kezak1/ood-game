#ifndef BOW_H
#define BOW_H

#include "weapon.h"

class Bow : public Weapon {
public:
    Bow(int _dmg, std::string s);
    virtual std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif

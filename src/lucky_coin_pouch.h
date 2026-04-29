#ifndef LUCKY_COIN_POUCH_H
#define LUCKY_COIN_POUCH_H

#include "magical_weapon.h"

class LuckyCoinPouch : public MagicalWeapon {
public:
    LuckyCoinPouch();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif
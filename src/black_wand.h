#ifndef BLACK_WAND_H
#define BLACK_WAND_H

#include "magical_weapon.h"
#include <memory>

class BlackWand : public MagicalWeapon {
public:
    BlackWand();
    std::string get_info() const override;
    std::unique_ptr<Item> equip(Player&p, std::unique_ptr<Item> self) override;
};

#endif
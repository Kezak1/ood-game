#ifndef UNLUCKY_MODIFIER_H
#define UNLUCKY_MODIFIER_H

#include "item_modifier.h"

class UnluckyModifier : public ItemModifier {
public:
    explicit UnluckyModifier(std::unique_ptr<Item> item);
    
    int get_lck_bonus() const override;
};

#endif
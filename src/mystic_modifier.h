#pragma once

#include "item_modifier.h"

#include <memory>
#include <format>

class MysticModifier : public ItemModifier {
public:
    explicit MysticModifier(std::unique_ptr<Item> item);
    
    int get_wis_bonus() const override;
};

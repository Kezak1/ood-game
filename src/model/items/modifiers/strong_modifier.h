#pragma once

#include "item_modifier.h"

#include <memory>


class StrongModifier : public ItemModifier {
public:
    explicit StrongModifier(std::unique_ptr<Item> item);
    
    int get_dmg() const override;
    std::string get_info() const override;
};

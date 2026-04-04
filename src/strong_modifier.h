#ifndef STRONG_MODIFIER_H
#define STRONG_MODIFIER_H

#include "item_modifier.h"

#include <memory>
#include <format>

class StrongModifier : public ItemModifier {
public:
    explicit StrongModifier(std::unique_ptr<Item> item);
    
    int get_dmg() const override;
    std::string get_info() const override;
};

#endif
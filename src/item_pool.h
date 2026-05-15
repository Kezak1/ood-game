#pragma once

#include "item.h"

#include <vector>

class ItemPool {
public:
    virtual ~ItemPool() = default;
    virtual std::vector<std::unique_ptr<Item>> items() const = 0;
};

#pragma once

#include "item.h"

class Currency : public Item {
public:
    Currency(std::string s);
    virtual std::string get_info() const override;
    bool goes_to_inv() const override;
};

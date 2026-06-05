#pragma once

#include "currency.h"

class Gold : public Currency {
public:
    Gold();
    std::string type_label() const override;
    bool on_pick_up(Player& p) const override;
};

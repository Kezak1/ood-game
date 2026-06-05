#pragma once

#include "currency.h"

class Coin : public Currency {
public:
    Coin();
    std::string type_label() const override;
    bool on_pick_up(Player& p) const override;
};

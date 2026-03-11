#ifndef COIN_H
#define COIN_H

#include "currency.h"

class Coin : public Currency {
public:
    Coin();
    bool on_pick_up(Player& p) const override;
};

#endif
#ifndef COIN_H
#define COIN_H

#include "currency.h"

class Coin : public Currency {
public:
    Coin();
    bool carryable(Player& p) const override;
};

#endif
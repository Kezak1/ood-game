#ifndef GOLD_H
#define GOLD_H

#include "currency.h"

class Gold : public Currency {
public:
    Gold();
    bool carryable(Player& p) const override;
};

#endif
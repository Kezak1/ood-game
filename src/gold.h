#ifndef GOLD_H
#define GOLD_H

#include "currency.h"

class Gold : public Currency {
public:
    Gold();
    bool on_pick_up(Player& p) const override;
};

#endif
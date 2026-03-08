#ifndef CURRENCY_H
#define CURRENCY_H

#include "item.h"

class Currency : public Item {
public:
    Currency(std::string s);
    virtual std::string get_info() const override;
};

#endif
#ifndef JUNK_H
#define JUNK_H

#include "item.h"

class Junk : public Item {
public:
    Junk(std::string s);
    virtual std::string get_info() const override;
    std::unique_ptr<Item> equip(Player& p, std::unique_ptr<Item> self) override;
};

#endif

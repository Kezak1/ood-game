#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#include <sstream>

class Weapon : public Item {
    int dmg;
public:
    Weapon(int _dmg, std::string s);
    virtual std::string get_info() const override;
    virtual std::string get_stats() const;
};

#endif
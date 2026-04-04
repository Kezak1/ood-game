#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

#include <sstream>

class Weapon : public Item {
protected:
    int dmg;
public:
    Weapon(int _dmg, std::string s);
    virtual std::string get_info() const override;
};

#endif
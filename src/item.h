#ifndef ITEM_H
#define ITEM_H

#include <string>


class Player;

class Item {
    std::string name;
public:
    Item(std::string s);

    const std::string& get_name();

    virtual ~Item() = default;
    virtual bool carryable(Player& p) const;
    virtual bool isweapon() const;  
};

#endif
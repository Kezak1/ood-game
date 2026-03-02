#ifndef ITEM_H
#define ITEM_H

#include <string>

class Player;

class Item {
    std::string name;
public:
    Item() : name("item") {}
    Item(std::string s) : name(s) {}

    const std::string& get_name();

    virtual ~Item() = default;
    virtual void player_pick_up(Player& p);
};

#endif
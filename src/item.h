#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

class Player;

class Item {
    std::string name;
public:
    Item(std::string s);

    const std::string& get_name() const;
    virtual std::string get_info() const;

    virtual bool on_pick_up(Player& p) const;
    virtual std::unique_ptr<Item> equip(Player&, std::unique_ptr<Item> self);

    virtual ~Item() = default;
};

#endif
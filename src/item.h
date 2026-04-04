#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

class Player;

class Item {
protected:
    std::string name;
public:
    Item(std::string s);
    virtual ~Item() = default;

    virtual std::string get_name() const;
    virtual std::string get_info() const = 0;
    
    virtual int get_dmg() const;
    virtual int get_str_bonus() const;
    virtual int get_dex_bonus() const;
    virtual int get_lck_bonus() const;
    virtual int get_agr_bonus() const;
    virtual int get_wis_bonus() const;

    virtual bool on_pick_up(Player& p) const;
    virtual std::unique_ptr<Item> equip(Player&, std::unique_ptr<Item> self);
};

#endif
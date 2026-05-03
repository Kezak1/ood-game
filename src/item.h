#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>   

class Player;
class Attack;
class Enemy;

class Item {
protected:
    std::string name;
public:
    Item(std::string s);
    virtual ~Item() = default;
    
    virtual std::string get_name() const;
    virtual std::string get_info() const;
    
    virtual int get_dmg() const;
    virtual int get_str_bonus() const;
    virtual int get_dex_bonus() const;
    virtual int get_lck_bonus() const;
    virtual int get_agr_bonus() const;
    virtual int get_wis_bonus() const;
    
    virtual bool goes_to_inv() const;
    virtual bool on_pick_up(Player& p) const;
    virtual std::unique_ptr<Item> equip(Player&, std::unique_ptr<Item> self);

    int attack(const Player& p, const Attack& a) const;
    int defense(const Player& p, const Attack& a) const;

    virtual int accept_attack(const Player&, const Attack&, const Item&) const;
    virtual int accept_defense(const Player&, const Attack&, const Item&) const;
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "utils.h"
#include "weapon.h"

#include <vector>
#include <memory>

class Player {
    int hp, str, dex, lck, agr, wis;
    int gold, coins;
    std::vector<std::unique_ptr<Item>> inventory;
    std::unique_ptr<Weapon> left_hand, right_hand, both_hands;  
public:
    Player();
    const int& get_hp() const;
    const int& get_str() const;
    const int& get_dex() const;
    const int& get_lck() const;
    const int& get_agr() const;
    const int& get_wis() const;

    const int& get_gold() const;
    void set_gold(int val);
    const int& get_coins() const;
    void set_coins(int val);

    const std::unique_ptr<Weapon>& get_left_weapon() const;
    void set_left_hand(std::unique_ptr<Weapon> w);
    std::unique_ptr<Weapon> take_left_weapon();

    const std::unique_ptr<Weapon>& get_right_weapon() const;
    void set_right_hand(std::unique_ptr<Weapon> w);
    std::unique_ptr<Weapon> take_right_weapon();
    
    const std::unique_ptr<Weapon>& get_both_weapon() const;
    void set_both_hands(std::unique_ptr<Weapon> w);
    std::unique_ptr<Weapon> take_both_weapon();

    const std::vector<std::unique_ptr<Item>>& get_inventory() const;
    void add_item(std::unique_ptr<Item> item);
    void insert_item(int idx, std::unique_ptr<Item> item);
    std::unique_ptr<Item> take_item(int idx);
};

#endif

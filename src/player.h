#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "utils.h"

#include <vector>
#include <memory>

class Player {
    int hp, str, dex, lck, agr, wis;
    int gold, coins;
    std::vector<std::unique_ptr<Item>> inventory;
    std::unique_ptr<Item> left_hand, right_hand;  
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

    const std::unique_ptr<Item>& get_left_hand() const;
    const std::unique_ptr<Item>& get_right_hand() const;

    const std::vector<std::unique_ptr<Item>>& get_inventory() const;

    void add_item(std::unique_ptr<Item> item);
    std::unique_ptr<Item> take_item(int idx);
};

#endif

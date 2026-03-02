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

    const std::vector<int> get_stats() const;
    const std::vector<std::unique_ptr<Item>>& get_inventory() const;

    void add_coin();
    void add_gold();

    void add_item(std::unique_ptr<Item> item);
    std::unique_ptr<Item> take_item(int idx);
};

#endif

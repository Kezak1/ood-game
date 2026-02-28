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
    
    /*
    bool empty_left_hand() const;
    bool empty_right_hand() const;
    bool empty_both_hands() const;

    void pick_to_left_hand(std::unique_ptr<Item> item);
    void pick_to_right_hand(std::unique_ptr<Item> item);
    void pick_to_both_hands(std::unique_ptr<Item> item);

    void add_elem(std::unique_ptr<Item> item);
    void remove_elem();
    */
};

#endif

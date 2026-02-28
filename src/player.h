#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

#include <vector>
#include <memory>

class Player {
    int r, c;
    int strength, dexterity, health, luck, aggression, wisdom;
    
    std::vector<std::unique_ptr<Item>> inventory;
    std::unique_ptr<Item> left_hand, right_hand;  
public:
    Player();

    bool empty_left_hand() const;
    bool empty_right_hand() const;
    bool empty_both_hands() const;

    void to_left_hand(Item& item);
    void to_right_hand(Item& item);
    void to_both_hands(Item& item);

    void add_elem(std::unique_ptr<Item> item);
    void remove_elem();
};

#endif

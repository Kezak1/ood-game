#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "item.h"
#include "utils.h"

#include <vector>
#include <memory>

class Player : public Entity {
    std::string name;
    int str, dex, lck, agr, wis;
    int gold, coins;

    std::vector<std::unique_ptr<Item>> inventory;
    static constexpr size_t max_inventory_cap = 6; 
    std::unique_ptr<Item> left_hand, right_hand, both_hands;  
public:
    Player(std::string name);
    int get_str() const;
    int get_dex() const;
    int get_lck() const;
    int get_agr() const;
    int get_wis() const;

    const int& get_gold() const;
    void set_gold(int val);
    const int& get_coins() const;
    void set_coins(int val);

    const std::unique_ptr<Item>& get_left_hand() const;
    void set_left_hand(std::unique_ptr<Item> w);
    std::unique_ptr<Item> take_left_hand();

    const std::unique_ptr<Item>& get_right_hand() const;
    void set_right_hand(std::unique_ptr<Item> w);
    std::unique_ptr<Item> take_right_hand();
    
    const std::unique_ptr<Item>& get_both_hands() const;
    void set_both_hands(std::unique_ptr<Item> w);
    std::unique_ptr<Item> take_both_hands();

    bool equip_in_single_hand(std::unique_ptr<Item>& item);
    bool equip_in_both_hands(std::unique_ptr<Item>& item);

    const std::vector<std::unique_ptr<Item>>& get_inventory() const;
    bool can_add_item() const;
    void add_item(std::unique_ptr<Item> item);
    void insert_item(int idx, std::unique_ptr<Item> item, bool restoring);
    std::unique_ptr<Item> take_item(int idx);

    std::string get_item_info(int idx) const;
    std::string get_left_hand_info() const;
    std::string get_right_hand_info() const;
    std::string get_both_hand_info() const;

    void take_dmg(int dmg);
};

#endif

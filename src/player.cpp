#include "player.h"

Player::Player() : 
    hp(100),
    str(next_random(0, 20)),
    dex(next_random(0, 20)),
    lck(next_random(0, 20)),
    agr(next_random(0, 20)),
    wis(next_random(0, 20)),
    gold(0),
    coins(0),
    left_hand(nullptr), 
    right_hand(nullptr) {
}

const std::vector<int> Player::get_stats() const {
    return {hp, str, dex, lck, agr, wis, gold, coins};
}

const std::vector<std::unique_ptr<Item>>& Player::get_inventory() const {
    return inventory;
}

void Player::add_coin() {
    coins++;
}

void Player::add_gold() {
    gold++;
}

void Player::add_item(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}


std::unique_ptr<Item> Player::take_item(int idx) {
    if(idx >= 1 && idx <= (int)inventory.size()) {
        throw std::out_of_range("idx");
    }
    auto res = std::move(inventory[idx]);
    inventory.erase(inventory.begin() + idx - 1);
    return res;
}
#include "player.h"
#include <memory>

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
    right_hand(nullptr),
    both_hands(nullptr) {
}

const int& Player::get_hp() const {
    return hp;
}

const int& Player::get_str() const {
    return str;
}

const int& Player::get_dex() const {
    return dex;
}

const int& Player::get_lck() const {
    return lck;
}

const int& Player::get_agr() const {
    return agr;
}

const int& Player::get_wis() const {
    return wis;
}

const int& Player::get_gold() const {
    return gold;
}

void Player::set_gold(int val) {
    gold = val;
}

const int& Player::get_coins() const {
    return coins;
}

void Player::set_coins(int val) {
    coins = val;
}

const std::unique_ptr<Item>& Player::get_left_hand() const {
    return left_hand;
}

const std::unique_ptr<Item>& Player::get_right_hand() const {
    return right_hand;
}

const std::unique_ptr<Item>& Player::get_both_hand() const {
    return both_hands;
}

const std::vector<std::unique_ptr<Item>>& Player::get_inventory() const {
    return inventory;
}

void Player::add_item(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

std::unique_ptr<Item> Player::take_item(int idx) {
    if(idx < 1 || idx > (int)inventory.size()) {
        throw std::out_of_range("idx");
    }
    auto res = std::move(inventory[idx - 1]);
    inventory.erase(inventory.begin() + idx - 1);
    return res;
}
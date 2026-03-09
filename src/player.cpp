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

void Player::set_left_hand(std::unique_ptr<Item> w) {
    left_hand = std::move(w);
}

std::unique_ptr<Item> Player::take_left_hand() {
    return std::move(left_hand);
}

const std::unique_ptr<Item>& Player::get_right_hand() const {
    return right_hand;
}

void Player::set_right_hand(std::unique_ptr<Item> w) {
    right_hand = std::move(w);
}

std::unique_ptr<Item> Player::take_right_weapon() {
    return std::move(right_hand);
}

const std::unique_ptr<Item>& Player::get_both_hands() const {
    return both_hands;
}

void Player::set_both_hands(std::unique_ptr<Item> w) {
    both_hands = std::move(w);
}

std::unique_ptr<Item> Player::take_both_hands() {
    return std::move(both_hands);
}

bool Player::equip_in_single_hand(std::unique_ptr<Item>& item) {
    if(both_hands) {
        return false;
    }

    if(!right_hand) {
        right_hand = std::move(item);
        return true;
    }
    if(!left_hand) {
        left_hand = std::move(item);
        return true;
    }
    
    return false;
}

bool Player::equip_in_both_hands(std::unique_ptr<Item>& item) {
    if(both_hands || left_hand || right_hand) {
        return false;
    }
    
    both_hands = std::move(item);
    return true;
}

const std::vector<std::unique_ptr<Item>>& Player::get_inventory() const {
    return inventory;
}

void Player::add_item(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Player::insert_item(int idx, std::unique_ptr<Item> item, bool restoring) {
    if(restoring) {
        if(idx < 1 || idx > (int)inventory.size() + 1) {
            throw std::out_of_range("idx");
        }

        if(idx == (int)inventory.size() + 1) {
            inventory.push_back(std::move(item));
        } else {
            inventory.insert(inventory.begin() + idx - 1, std::move(item));
        }
        return;
    }
    
    if(idx < 1 || idx > (int)inventory.size()) {
        throw std::out_of_range("idx");
    }
    inventory.insert(inventory.begin() + idx - 1, std::move(item));
}

std::unique_ptr<Item> Player::take_item(int idx) {
    if(idx < 1 || idx > (int)inventory.size()) {
        throw std::out_of_range("idx");
    }
    auto res = std::move(inventory[idx - 1]);
    inventory.erase(inventory.begin() + idx - 1);
    return res;
}

std::string Player::get_item_info(int idx) const {
    if(idx < 1 || idx > (int)inventory.size()) {
        throw std::out_of_range("idx");
    }

    return inventory[idx - 1]->get_info();
}

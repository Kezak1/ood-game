#include "player.h"
#include "entity.h"
#include "utils.h"
#include <memory>

Player::Player() : 
    Entity(1, 1),
    str(20),
    dex(20),
    lck(20),
    agr(20),
    wis(20),
    gold(0),
    coins(0),
    left_hand(nullptr), 
    right_hand(nullptr),
    both_hands(nullptr) {
}

int Player::get_str() const {
    return str;
}

int Player::get_dex() const {
    return dex;
}

int Player::get_lck() const {
    int bonus = 0;

    if(left_hand) bonus += left_hand->get_lck_bonus();
    if(right_hand) bonus += right_hand->get_lck_bonus();
    if(both_hands) bonus += both_hands->get_lck_bonus();

    return std::max(lck + bonus, 0);
}

int Player::get_agr() const {
    return agr;
}

int Player::get_wis() const {
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

std::unique_ptr<Item> Player::take_right_hand() {
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

std::string Player::get_left_hand_info() const {
    if(!left_hand) {
        throw custom_exception("null left hand");
    }

    return left_hand->get_info();
}

std::string Player::get_right_hand_info() const {
    if(!right_hand) {
        throw custom_exception("null right hand");
    }
    
    return right_hand->get_info();
}

std::string Player::get_both_hand_info() const {
    if(!both_hands) {
        throw custom_exception("null both hands");
    }
    
    return both_hands->get_info();
}

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
    right_hand(nullptr)
    {}

/*
bool Player::empty_left_hand() const {
    return left_hand == nullptr;
}

bool Player::empty_right_hand() const {
    return right_hand == nullptr;
}

bool Player::empty_both_hands() const {
    return empty_left_hand() && empty_right_hand();
}
*/
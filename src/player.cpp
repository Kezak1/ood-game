#

#include "player.h"

#include <random>

int next_random(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(l, r);

    return dist(gen);
}

Player::Player() : r(0), c(0), left_hand(nullptr), right_hand(nullptr) {
    strength = next_random(0, 20);
    dexterity = next_random(0, 20);
    health = next_random(0, 20);
    luck = next_random(0, 20);
    aggression = next_random(0, 20);
    wisdom = next_random(0, 20);
}

bool Player::empty_left_hand() const {
    return left_hand == nullptr;
}

bool Player::empty_right_hand() const {
    return right_hand == nullptr;
}

bool Player::empty_both_hands() const {
    return empty_left_hand() && empty_right_hand();
}

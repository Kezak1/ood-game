#include "coin.h"
#include "player.h"

Coin::Coin() : Currency("coin") {};

bool Coin::on_pick_up(Player& p) const {
    p.set_coins(p.get_coins() + 1);
    return false;
}
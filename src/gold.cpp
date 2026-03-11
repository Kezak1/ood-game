#include "gold.h"
#include "player.h"

Gold::Gold() : Currency("gold") {};

bool Gold::on_pick_up(Player& p) const {
    p.set_gold(p.get_gold() + 1);
    return false;
}
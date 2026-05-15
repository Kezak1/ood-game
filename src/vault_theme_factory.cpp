#include "vault_theme_factory.h"
#include "layout_strategy.h"
#include "lucky_coin_pouch.h"
#include "vault_layout.h"
#include "utils.h"
#include "gold.h"
#include "coin.h"

#include <memory>
#include <vector>

std::string VaultThemeFactory::intro() const {
    return "You feel an itch in your wallet";
}

std::unique_ptr<LayoutStrategy> VaultThemeFactory::create_layout() const {
    return std::make_unique<VaultLayout>();
}

std::vector<std::unique_ptr<Item>> VaultThemeFactory::create_item_pool() const {
    std::vector<std::unique_ptr<Item>> res;
    int rand = next_random(0, 19);
    for(int i = 0; i < 20; i++) {
        if(i > rand) {
            res.push_back(std::make_unique<Gold>());
        } else {
            res.push_back(std::make_unique<Coin>());
        }
    }
    return res;
}

std::unique_ptr<Item> VaultThemeFactory::create_artifact() const {
    return std::make_unique<LuckyCoinPouch>();
}

std::vector<Enemy> VaultThemeFactory::create_enemy_roster() const {
    std::vector<Enemy> res;
    res.push_back(Enemy("Safe", -1, -1, 10, 10, 100));
    res.push_back(Enemy("Briefcase", -1, -1, 23, 5, 60));
    return res;
}

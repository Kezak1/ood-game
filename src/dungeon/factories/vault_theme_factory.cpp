#include "vault_theme_factory.h"
#include "dagger.h"
#include "great_sword.h"
#include "layout_strategy.h"
#include "lucky_coin_pouch.h"
#include "skeleton.h"
#include "strong_modifier.h"
#include "unlucky_modifier.h"
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
    for(int i = 0; i < 10; i++) {
        if(!next_random(0, 4)) {
            auto item = std::make_unique<Dagger>();
            if(!next_random(0, 4)) {
                res.push_back(std::make_unique<StrongModifier>(std::make_unique<UnluckyModifier>(std::move(item))));
            } else {
                res.push_back(std::move(item));
            }
        } else {
            res.push_back(std::make_unique<GreatSword>());
        }    
    }
    return res;
}

std::unique_ptr<Item> VaultThemeFactory::create_artifact() const {
    return std::make_unique<LuckyCoinPouch>();
}

std::vector<std::function<std::unique_ptr<Enemy>(int, int, Logger&)>> VaultThemeFactory::create_enemy_roster() const {
    return {
        [](int r, int c, Logger& logger) {
            return std::make_unique<Skeleton>("Safe", r, c, 10, 10, 100, logger);
        },
        [](int r, int c, Logger& logger) {
            return std::make_unique<Skeleton>("Briefcase", r, c, 23, 5, 60, logger);
        }
    };
}

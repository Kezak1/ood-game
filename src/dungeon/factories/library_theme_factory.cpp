#include "library_theme_factory.h"
#include "black_wand.h"
#include "layout_strategy.h"
#include "library_layout.h"
#include "utils.h"
#include "old_book.h"
#include "strange_idol.h"
#include "mystic_modifier.h"
#include "unlucky_modifier.h"
#include "goblin.h"
#include "staff.h"

#include <memory>
#include <vector>

std::string LibraryThemeFactory::intro() const {
    return "The smell of old books fills the air";
}

std::unique_ptr<LayoutStrategy> LibraryThemeFactory::create_layout() const {
    return std::make_unique<LibraryLayout>();
}

std::vector<std::unique_ptr<Item>> LibraryThemeFactory::create_item_pool() const {
    std::vector<std::unique_ptr<Item>> res;
    int rand = next_random(0, 9);
    for(int i = 0; i < 10; i++) {        
        if(i >= rand) {
            auto item = std::make_unique<OldBook>();
            if(next_random(0, 1)) {
                res.push_back(std::move(item));
            } else {
                res.push_back(std::make_unique<MysticModifier>(std::move(item)));
            }
        } else {
            auto item = std::make_unique<StrangeIdol>();
            if(next_random(0, 1)) {
                res.push_back(std::move(item));
            } else {
                res.push_back(std::make_unique<UnluckyModifier>(std::move(item)));
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        auto item = std::make_unique<Staff>();
        if(!next_random(0, 9)) {
            res.push_back(std::make_unique<MysticModifier>(std::move(item)));
        } else {
            res.push_back(std::move(item));
        }
    }

    return res;
}

std::unique_ptr<Item> LibraryThemeFactory::create_artifact() const {
    return std::make_unique<BlackWand>();
}

std::vector<std::function<std::unique_ptr<Enemy>(int, int, Logger&)>> LibraryThemeFactory::create_enemy_roster() const {
    return {
        [](int r, int c, Logger& logger) {
            return std::make_unique<Goblin>("Mage", r, c, next_random(20, 30), next_random(2, 6), next_random(55, 70), logger);
        },
        [](int r, int c, Logger& logger) {
            return std::make_unique<Goblin>("Apprentice", r, c, next_random(10, 18), next_random(1, 3), next_random(45, 55), logger);
        }
    };
}
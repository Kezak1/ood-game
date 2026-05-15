#include "library_theme_factory.h"
#include "black_wand.h"
#include "layout_strategy.h"
#include "library_layout.h"
#include "utils.h"
#include "old_book.h"
#include "strange_idol.h"
#include "mystic_modifier.h"
#include "unlucky_modifier.h"

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
            res.push_back(std::make_unique<MysticModifier>(std::make_unique<OldBook>()));
        } else {
            res.push_back(std::make_unique<UnluckyModifier>(std::make_unique<StrangeIdol>()));
        }
    }

    return res;
}

std::unique_ptr<Item> LibraryThemeFactory::create_artifact() const {
    return std::make_unique<BlackWand>();
}

std::vector<std::function<std::unique_ptr<Enemy>(int, int)>> LibraryThemeFactory::create_enemy_roster() const {
    return {
        [](int r, int c) {
            return std::make_unique<Enemy>("Mage", r, c, next_random(20, 30), next_random(2, 6), next_random(45, 55));
        }
    };
}
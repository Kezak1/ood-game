#include "metal_theme_factory.h"
#include "enemy.h"
#include "layout_strategy.h"
#include "metal_layout.h"
#include "metal_fragment.h"
#include "rock.h"
#include "blaster.h"
#include "skeleton.h"
#include "goblin.h"

#include <memory>
#include <vector>

std::string MetalThemeFactory::intro() const {
    return "The clang of metal echoes off the walls";
}

std::unique_ptr<LayoutStrategy> MetalThemeFactory::create_layout() const {
    return std::make_unique<MetalLayout>();
}

std::vector<std::unique_ptr<Item>> MetalThemeFactory::create_item_pool() const {
    std::vector<std::unique_ptr<Item>> res;
    for(int i = 0; i < 25; i++) {
        res.push_back(std::make_unique<MetalFragment>());
    }
    for(int i = 0; i < 4; i++) {
        res.push_back(std::make_unique<Rock>());
    }

    return res;
}

std::unique_ptr<Item> MetalThemeFactory::create_artifact() const {
    return std::make_unique<Blaster>();
}

std::vector<std::function<std::unique_ptr<Enemy>(int, int)>> MetalThemeFactory::create_enemy_roster() const {
    return {
        [](int r, int c) {
            return std::make_unique<Goblin>("Cleaning Robot", r, c, 20, 5, 50);
        },
        [](int r, int c) {
            return std::make_unique<Goblin>("Dog Robot", r, c, 20, 5, 50);
        },
        [](int r, int c) {
            return std::make_unique<Skeleton>("Drone", r, c, 25, 8, 70);
        }
    };
}

#pragma once

#include "enemy.h"
#include "layout_strategy.h"
#include "item_pool.h"
#include "item.h"

#include <string>
#include <memory>

class DungeonThemeFactory {
public:
    virtual ~DungeonThemeFactory() = default;

    virtual std::string intro() const = 0;
    virtual std::unique_ptr<LayoutStrategy> create_layout() const = 0;
    virtual std::vector<std::unique_ptr<Item>> create_item_pool() const = 0;
    virtual std::unique_ptr<Item> create_artifact() const = 0;
    virtual std::vector<Enemy> create_enemy_roster() const = 0;
};

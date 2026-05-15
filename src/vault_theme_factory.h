#pragma once

#include "dungeon_theme_factory.h"

class VaultThemeFactory : public DungeonThemeFactory {
public:
    std::string intro() const override;
    std::unique_ptr<LayoutStrategy> create_layout() const override;
    std::vector<std::unique_ptr<Item>> create_item_pool() const override;
    std::unique_ptr<Item> create_artifact() const override;
    std::vector<Enemy> create_enemy_roster() const override;
};
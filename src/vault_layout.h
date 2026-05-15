#pragma once

#include "dungeon_builder_facade.h"
#include "layout_strategy.h"

class VaultLayout : public LayoutStrategy {
public:
    void apply(DungeonBuilderFacade& b) const override;
};

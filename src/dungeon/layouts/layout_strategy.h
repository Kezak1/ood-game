#pragma once

#include "dungeon_builder_facade.h"

class LayoutStrategy {
public:
    virtual ~LayoutStrategy() = default; 
    virtual void apply(DungeonBuilderFacade& b) const = 0;
};

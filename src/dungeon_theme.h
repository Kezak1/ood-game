#ifndef DUNGEON_THEME_H
#define DUNGEON_THEME_H

#include "dungeon_builder_facade.h"

class DungeonTheme {
public:
    virtual ~DungeonTheme() = default;
    
    virtual std::string intro() const = 0;
    virtual void generate(DungeonBuilderFacade& builder) const = 0;
};

#endif
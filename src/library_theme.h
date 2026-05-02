#ifndef LIBRARY_THEME_H
#define LIBRARY_THEME_H

#include "dungeon_builder_facade.h"
#include "dungeon_theme.h"

class LibraryTheme : public DungeonTheme {
    std::string intro() const override;
    void generate(DungeonBuilderFacade& builder) const override;
};

#endif
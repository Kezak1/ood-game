#include "metal_theme.h"
#include "dungeon_builder_facade.h"
#include "metal_fragment.h"
#include "utils.h"
#include "blaster.h"

#include <memory>

std::string MetalTheme::intro() const {
    return "The clang of metal echoes off the walls";
}

void MetalTheme::generate(DungeonBuilderFacade& builder) const {
    for(int i = 0; i < 20; i++) {
        builder.add_random_chamber(next_random(2, 4));
    }
    builder.connect_empty();

    auto a = builder.get_empty_pos();

    for(int i = 0; i < 30; i++) {
        int idx = next_random(0, (int)a.size() - 1);
        auto [r, c] = a[idx];
        if(i == 0) {
            builder.add_item(r, c, std::make_unique<Blaster>());
            continue;
        }
        builder.add_item(r, c, std::make_unique<MetalFragment>());
    }

    a = builder.get_no_items_pos();

    for(int i = 0; i < 6; i++) {
        int idx = next_random(0, (int)a.size() - 1);
        auto [r, c] = a[idx];
        builder.add_enemy("Cleaning Robot", r, c, 20, 5, 50);
        a.erase(a.begin() + idx);
    }
}
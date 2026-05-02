#include "library_theme.h"
#include "black_wand.h"
#include "dungeon_builder_facade.h"
#include "utils.h"
#include "old_book.h"
#include "strange_idol.h"
#include "black_wand.h"
#include "mystic_modifier.h"
#include "unlucky_modifier.h"

#include <memory>

std::string LibraryTheme::intro() const {
    return "The smell of old books fills the air";
}

void LibraryTheme::generate(DungeonBuilderFacade& builder) const {
    for(int i = 0; i < 15; i++) {
        builder.add_random_path();    
    }
    builder.add_random_chamber(5);
    builder.connect_empty();

    auto a = builder.get_empty_pos();

    for(int i = 0; i < 11; i++) {
        int idx = next_random(0, (int)a.size() - 1);
        auto [r, c] = a[idx];
        if(i == 0) {
            builder.add_item(r, c, std::make_unique<BlackWand>());
        }
        
        if(next_random(0,1)) {
            builder.add_item(r, c, std::make_unique<MysticModifier>(std::make_unique<OldBook>()));
        } else {
            builder.add_item(r, c, std::make_unique<UnluckyModifier>(std::make_unique<StrangeIdol>()));
        }
    }

    a = builder.get_no_items_pos();

    for(int i = 0; i < 6; i++) {
        int idx = next_random(0, (int)a.size() - 1);
        auto [r, c] = a[idx];
        builder.add_enemy("Mage", r, c, next_random(20, 30), next_random(2, 6), next_random(45, 55));
        a.erase(a.begin() + idx);
    }
}
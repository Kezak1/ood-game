#include "vault_layout.h"
#include "dungeon_builder_facade.h"

void VaultLayout::apply(DungeonBuilderFacade& b) const {
    for(int i = 0; i < 10; i++) {
        b.add_random_path();
    }
    b.add_center_room(8, 8);
    b.connect_empty();
}

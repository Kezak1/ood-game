#include "metal_layout.h"
#include "utils.h"

void MetalLayout::apply(DungeonBuilderFacade& b) const {
    for(int i = 0; i < 20; i++) {
        b.add_random_chamber(next_random(2, 4));
    }
    b.connect_empty();
}
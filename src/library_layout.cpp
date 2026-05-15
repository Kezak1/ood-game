#include "library_layout.h"

void LibraryLayout::apply(DungeonBuilderFacade& b) const {
    for(int i = 0; i < 15; i++) {
        b.add_random_path();    
    }
    b.add_random_chamber(5);
    b.connect_empty();
}
#include "vault_theme.h"
#include "lucky_coin_pouch.h"
#include "utils.h"
#include <memory>

std::string VaultTheme::intro() const {
    return "You feel an itch in your wallet";
}

void VaultTheme::generate(DungeonBuilderFacade& builder) const {
    for(int i = 0; i < 10; i++) {
        builder.add_random_path();
    }
    builder.add_center_room(8, 8);
    builder.connect_empty();

    auto p = builder.get_empty_pos();

    for(int i = 0; i <= 10 && !p.empty(); i++) {
        // todo make so its imposible to have enemy and item in one cell
        int idx = next_random(0, (int)p.size() - 1);
        auto [r, c] = p[idx];
        p.erase(p.begin() + idx);

        if(i == 0) {
            builder.add_item(r, c, std::make_unique<LuckyCoinPouch>());
            continue;
        }
        std::string name = "safe";
        int hp = 80;
        if(next_random(0, 1)) {
            name = "briefcase";
            hp = 60;
        }

        builder.add_enemy(name, r, c, 25, hp);
    }

    builder.add_random_currencies(20);
    
} 

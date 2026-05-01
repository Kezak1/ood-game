#include "vault_theme.h"
#include "lucky_coin_pouch.h"
#include "strong_modifier.h"
#include "utils.h"

std::string VaultTheme::intro() const {
    return "You feel an itch in your wallet";
}

void VaultTheme::generate(DungeonBuilderFacade& builder) const {
    for(int i = 0; i < 10; i++) {
        builder.add_random_path();
    }
    builder.add_center_room(8, 8);
    builder.connect_empty();

    builder.add_random_currencies(20);

    auto a = builder.get_no_items_pos();

    for(int i = 0; i <= 10 && !a.empty(); i++) {
        int idx = next_random(0, (int)a.size() - 1);
        auto [r, c] = a[idx];
        a.erase(a.begin() + idx);

        if(i == 0) {
            std::unique_ptr<Item> pouch = std::make_unique<LuckyCoinPouch>();
            if(next_random(0, 1)) {
                pouch = std::make_unique<StrongModifier>(std::move(pouch));
            }
            builder.add_item(r, c, std::move(pouch));
            continue;
        }
        
        std::string name = "safe";
        int hp = 80;
        int attack = 15;
        int armor = 10;
        if(next_random(0, 1)) {
            name = "briefcase";
            hp = 60;
            attack = 20;
            armor = 3;
        }

        builder.add_enemy(name, r, c, attack, armor, hp);
    }
} 

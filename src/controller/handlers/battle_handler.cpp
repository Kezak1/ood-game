#include "battle_handler.h"
#include "game_model.h"
#include "utils.h"
#include "view.h"
#include "item.h"
#include "normal_attack.h"
#include "stealth_attack.h"
#include "magical_attack.h"

#include <format>
#include <memory>

namespace {
    const Item* choose_battle_item(const Player& p, const std::string& hand) {
        if(hand == "left") {
            return p.get_left_hand().get();
        } else if(hand == "right") {
            return p.get_right_hand().get();
        } else if(hand == "both") {
            return p.get_both_hands().get();
        }
        return nullptr;
    }

    std::string auto_choose_hand(const Player& p) {
        if(p.get_both_hands()) {
            return "both";
        }
        if(p.get_left_hand() && !p.get_right_hand()) {
            return "left";
        }
        if(!p.get_left_hand() && p.get_right_hand()) {
            return "right";
        }
        return "";
    }

    std::unique_ptr<Attack> choose_battle_attack(std::string attack_type) {
        if(attack_type == "normal") {
            return std::make_unique<NormalAttack>();
        }
        if(attack_type == "stealth") {
            return std::make_unique<StealthAttack>();
        }
        if(attack_type == "magical") {
            return std::make_unique<MagicalAttack>();
        }

        return nullptr;
    }
}


std::optional<bool> BattleHandler::handle(GameModel& model, View& view, char key) {
    if(tolower(key) != 'f') {
        return std::nullopt;
    }
    
    //battle
    int enemy_idx = model.player_enemy_map_value();
    bool ok = model.check_battle_start(enemy_idx);
    if(!ok) {
        return false;
    }

    view.enter_battle_screen();

    bool player_won = true;
    while(!model.player().is_dead() && !model.get_enemies()[enemy_idx]->is_dead()) {
        view.render_battle(model, enemy_idx);

        view.tell("PLAYER:");

        std::string input = auto_choose_hand(model.player());
        if(input == "") {
            input = view.ask("Choose item, enter 'left'/'right'/'both' (or 'give up'): ");
            if(input == "give up") {
                model.player_give_up(enemy_idx);
                player_won = false;
                break;
            }
        }

        const Item* item = choose_battle_item(model.player(), input);
        if(!item) {
            view.tell("ERROR: invalid hand");
            view.wait_any_key();
            continue;
        }

        std::string atk_input = view.ask("Choose attack type, enter 'normal'/'stealth'/'magical' (or 'give up'): ");
        if(atk_input == "give up") {
            model.player_give_up(enemy_idx);
            player_won = false;
            break;
        }

        std::unique_ptr<Attack> attack = choose_battle_attack(atk_input);
        
        if(!attack) {
            view.tell("ERROR: invalid attack");
            view.wait_any_key();
            continue;
        }

        RoundResult res = model.battle_round(enemy_idx, *item, *attack);
        view.render_battle(model, enemy_idx);
        view.tell(std::format("PLAYER dealt {} damage", res.player_dmg_dealt));

        if(res.enemy_died) {
            view.tell(std::format("{} was defeated", all_toupper(model.get_enemies()[enemy_idx]->get_name())));
            model.kill_enemy(enemy_idx);
            view.wait_any_key();
            break;
        }

        view.tell(std::format("Enemy dealt {} damage", res.enemy_dmg_dealt));

        if (res.player_died) {
            view.tell("PLAYER lost a battle");
            player_won = false;
            view.wait_any_key();
            break;
        }

        view.wait_any_key();
    }

    view.exit_battle_screen();
    
    return !player_won;
} 
#include "game.h"
#include "begin_battle_handler.h"
#include "dungeon_builder.h"
#include "equipment_handler.h"
#include "inventory_handler.h"
#include "item.h"
#include "magical_attack.h"
#include "normal_attack.h"
#include "quit_handler.h"
#include "stealth_attack.h"
#include "utils.h"
#include "vault_theme.h"

#include <memory>
#include <cstring>

Game::Game() : p(Player()) {
    init_handlers();
    DungeonBuilder d(true);
    VaultTheme vt;
    
    auto res = d.build(vt);

    board = std::move(res.board);
    capabilities = res.capabilities;
    enemies = res.enemies;

    enemy_map.assign(ROWS, std::vector<int>(COLS, -1));
    int idx = 0;
    for(auto& e : enemies) {
        enemy_map[e.get_r()][e.get_c()] = idx++;
    }
}

void Game::main_loop() {
    full_clear();
    hide_cursor();
    set_raw_mode(true);

    render_state();
    cur_action_info();

    while(1) {
        char k = getchar();
        k = tolower(k);

        to_start_cursor();
        render_state();
        cur_action_info();

        bool handled = false;
        bool quit = false;

        for(auto& handler : handlers) {
            if(auto res = handler->handle(*this, k)) {
                handled = true;
                quit = *res;
                break;
            }
        }

        if(quit) {
            break;
        }

        if (!handled) {
            std::cerr << "invalid key pressed\n(to continue press any key)";
            getchar();
        }
    
        to_start_cursor();
        render_state();
        cur_action_info();
       
        std::cout << std::flush;
    }

    unhide_cursor();
    set_raw_mode(false);
}

void Game::init_handlers() {
    handlers.clear();

    handlers.push_back(std::make_unique<QuitHandler>());
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<EquipmentHandler>());
    handlers.push_back(std::make_unique<InventoryHandler>());
    handlers.push_back(std::make_unique<BeginBattleHandler>());
}

void Game::player_move_up() {
    if(!board[p.get_r() - 1][p.get_c()].is_wall()) {
        p.set_r(p.get_r() - 1);
    }
}

void Game::player_move_down() {
    if(!board[p.get_r() + 1][p.get_c()].is_wall()) {
        p.set_r(p.get_r() + 1);
    }
}

void Game::player_move_left() {
    if(!board[p.get_r()][p.get_c() - 1].is_wall()) {
        p.set_c(p.get_c() - 1);
    }
}

void Game::player_move_right() {
    if(!board[p.get_r()][p.get_c() + 1].is_wall()) {
        p.set_c(p.get_c() + 1);
    }
}

bool Game::is_enemy_pos(int r, int c) {
    return enemy_map[r][c] >= 0;
}

void Game::render_state() {
    print_player_stats();
    print_player_inventory();
    print_player_wallet();
    print_player_hands();
    print_instructions();
    std::cout << "\n";

    std::stringstream ss;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(board[r][c].is_wall()) {
                ss << C_WALL << C_WALL;
                continue;
            }
            if(r == p.get_r() && c == p.get_c()) {
                ss << C_PLAYER;
            } else {
                ss << C_EMPTY;
            }

            if(is_enemy_pos(r, c)) {
                ss << C_ENEMY;
            } else if(board[r][c].empty()) {
                ss << C_EMPTY;
            } else {
                ss << C_ITEMS;
            }
        }
        ss << '\n';
    }
    std::cout << ss.str();
}  

void Game::cur_action_info() {
    full_clear_from_cursor();
    auto& items = board[p.get_r()][p.get_c()].get_items();
    std::cout << "LOG: ";
    if(is_enemy_pos(p.get_r(), p.get_c())) {
        int idx = player_enemy_map_value();
        std::cout << std::format("{} - hp({}), attack({}), armor({})\n", enemies[idx].get_name(), enemies[idx].get_hp(), enemies[idx].get_attack(), enemies[idx].get_arrmor());
    } else if(items.empty()) {
        std::cout << "standing on empty cell\n";
    } else {
        std::cout << "standing on following items\n";
        int idx = 1;
        std::cout << "{ ";
        for(auto& i : items) {
            std::cout << std::format("{}.[{}] ", idx++, i->get_name());
        }
        std::cout << "}\n";
    }
}

void Game::print_player_wallet() {
    std::string out = std::format("COINS: {:<5} GOLD: {:<5}\n", p.get_coins(), p.get_gold());
    clear_line_cursor();
    std::cout << out;
}

void Game::print_player_stats() {
    std::string out = std::format(
        "PLAYER: HP {:3}/100 | STR {:2} | DEX {:2} | LCK {:2} | AGR {:2} | WIS {:2}\n",
        p.get_hp(), p.get_str(), p.get_dex(), p.get_lck(), p.get_agr(), p.get_wis(), p.get_gold(), p.get_coins()
    );

    clear_line_cursor();
    std::cout << out;
}

void Game::print_player_inventory() {
    auto& inventory = p.get_inventory();

    std::stringstream out;
    out << "INVENTORY: { ";
    int idx = 1;
    for(auto& i : inventory) {
        out << std::format("{}.[{}] ", idx++, i->get_name());
    }
    out << "}\n";

    clear_line_cursor();
    std::cout << out.str();
}

void Game::print_player_hands() {
    std::stringstream out;
    out << "EQUIPED:";
    if(p.get_left_hand()) {
        out << std::format(" {}(left)", p.get_left_hand()->get_name());
    }

    if(p.get_right_hand()) {
        out << std::format(" {}(right)", p.get_right_hand()->get_name());
    }

    if(p.get_both_hands()) {
        out << std::format(" {}(both)", p.get_both_hands()->get_name());
    }
    out << "\n";
    
    clear_line_cursor();
    std::cout << out.str();
}

void Game::print_instructions() {
    std::stringstream out;
    out << "QUIT(Q) | ";
    if(capabilities.can_move) {
        out << "MOVE(WASD) | ";
    }
    if(capabilities.has_currency && !capabilities.has_items) {
        out << "PICK UP(E) | ";
    }
    if(capabilities.has_items) {
        out << "PICK UP(E) | DROP(G) | EQUIP(J) | UNEQUIP(K) | GET INFO(I) | ";
    }
    if(capabilities.has_enemies) {
        out << "BATTLE(F) | ";
    }
    
    auto strout = out.str();
    strout.pop_back();
    strout.pop_back();

    clear_line_cursor();
    std::cout << strout << '\n';
}

void Game::player_try_pick_up_item() {
    auto& cell = board[p.get_r()][p.get_c()];

    if(cell.empty()) {
        return;
    }

    set_raw_mode(false);
    unhide_cursor();

    std::string input = "1";

    if(cell.get_items().size() > 1) {
        std::cout << "Enter index which item to pick up (to cancel write 'cancel'): ";
        
        std::getline(std::cin,input);
        
        if(input == "cancel") {
            set_raw_mode(true);
            hide_cursor();
            return;
        }
    }
    
    set_raw_mode(true);
    hide_cursor();

    try {
        auto item = cell.take_item(std::stoi(input));
        if(item->on_pick_up(p)) {
            p.add_item(std::move(item));
        }
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        getchar();
    }
}

void Game::player_try_drop_item() {
    if(p.get_inventory().empty()) {
        return;
    }
    set_raw_mode(false);
    unhide_cursor();

    std::cout << "Enter index of item to drop it from inventory (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();

    if(input == "cancel") {
        return;
    }

    Cell& cell = board[p.get_r()][p.get_c()];

    try {
        int idx = std::stoi(input);
        cell.add_item(p.take_item(idx));
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        getchar();
    }
}

void Game::player_try_equip_weapon() {
    if(p.get_inventory().empty()) {
        return;
    }

    set_raw_mode(false);
    unhide_cursor();

    std::cout << "Enter index of item from inventory (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();

    if(input == "cancel") {
        return;
    }

    try {
        int idx = std::stoi(input);

        std::unique_ptr<Item> item = p.take_item(idx);
        Item* raw_item = item.get();
        item = raw_item->equip(p, std::move(item));
        if(item) {
            p.insert_item(idx, std::move(item), true);
            throw custom_exception("cannot equip this item");
        }
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        getchar();
    }
}

void Game::player_try_unequip_weapon() {
    set_raw_mode(false);
    unhide_cursor();

    std::cout << "Enter 'left'/'right'/'both' to unequip (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();
    try {
        if(input == "cancel") {
            return;
        } else if(input == "left") {
            auto& left = p.get_left_hand();
            if(!left) {
                return;
            }
            p.add_item(p.take_left_hand());
        } else if(input == "right") {
            auto& right = p.get_right_hand();
            if(!right) {
                return;
            }
            p.add_item(p.take_right_hand());
        } else if(input == "both") {
            auto& both = p.get_both_hands();
            if(!both) {
                return;
            }
            p.add_item(p.take_both_hands());
        } else {
            throw custom_exception("invalid input");
        }
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        getchar();
    }
}

void Game::player_try_get_item_info() {
    if(p.get_inventory().empty()) {
        return;
    }
    set_raw_mode(false);
    unhide_cursor();

    std::cout << "Enter inventory index or 'left'/'right'/'both' to get info about chosen item (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();

    if(input == "cancel") {
        return;
    }

    try {
        std::stringstream ss;
        ss << "INFO: ";

        if(input == "left") {
            ss << p.get_left_hand_info();
        } else if(input == "right") {
            ss << p.get_right_hand_info();
        } else if(input == "both") {
            ss << p.get_both_hand_info();
        } else {
            int idx = std::stoi(input);
            ss << p.get_item_info(idx);
        }

        ss << "\n(to continue press any key)";
        std::cout << ss.str();
        getchar();
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n(to continue press any key)";
        getchar();
    }
}

void Game::print_battlefield() {
    std::cout << R"(.-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.
|                                                 |
|                                 @@@@@@@@@@@     |
|                                @@@@@@@@@@@@@    |
|                               @@@@       @@@@   | 
|    ________                   @@@  @@@@@  @@@   !
!   /  ___| |                   @@@  @@@@@  @@@   :
:  /  /	  | |                   @@@  @@@@@  @@@   :
: |  |	  | |                   @@@__@@@@@__@@@   .
.  \  \___| |                   @@@@       @@@@   : 
.   \_____| |                  / @@@@@@@@@@@@@ \  :
:         | |                  \  @@@@@@@@@@@  /  :
:    _____| |_____              \_____________/   !
!   /     | |     \                               |
|  /      |_|      \                              |
|  \               /                              |
|   \_____________/                               |
|                                                 |
`-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
)";
}

void Game::print_enemy_hp(int enemy_idx) {
    auto& e = enemies[enemy_idx];
    std::string out = std::format("{}: HP {:3}/{}\n", all_toupper(e.get_name()), e.get_hp(), e.get_max_hp());
    clear_line_cursor();
    std::cout << out;
}

void Game::render_battle_state(int enemy_idx) {
    full_clear();
    print_player_stats();
    print_player_hands();
    std::cout << '\n';
    print_enemy_hp(enemy_idx);
    print_battlefield();
}

bool Game::player_has_equipped_item() const {
    return p.get_left_hand() || p.get_right_hand() || p.get_both_hands();
}

const Item* Game::choose_battle_item() const {
    if(p.get_both_hands()) {
        return p.get_both_hands().get();
    }
    if(p.get_left_hand() && !p.get_right_hand()) {
        return p.get_left_hand().get();
    }
    if(!p.get_left_hand() && p.get_right_hand()) {
        return p.get_right_hand().get();
    }
    if(!player_has_equipped_item()) {
        return nullptr;
    }

    std::cout << "Choose item, enter 'left'/'right'/'both' (or 'give up'): ";

    std::string hold;
    std::getline(std::cin, hold);

    if(hold == "give up") {
        throw custom_exception("give up");
    }

    if(hold == "left") {
        if(!p.get_left_hand()) {
            throw custom_exception("left is null");
        }
        return p.get_left_hand().get();    
    }

    if(hold == "right") {
        if(!p.get_right_hand()) {
            throw custom_exception("right is null");
        }
        return p.get_right_hand().get();
    }

    if(hold == "both") {
        if(!p.get_both_hands()) {
            throw custom_exception("both is null");
        }
        return p.get_both_hands().get();
    }

    throw custom_exception("invalid input");
}

std::unique_ptr<Attack> Game::choose_battle_attack() const {
    std::cout << "Choose attack type, enter 'normal'/'stealth'/'magical' (or 'give up'): ";

    std::string attack_type;
    std::getline(std::cin, attack_type);

    if(attack_type == "give up") {
        throw custom_exception("give up");
    }

    if(attack_type == "normal") {
        return std::make_unique<NormalAttack>();
    }

    if(attack_type == "stealth") {
        return std::make_unique<StealthAttack>();
    }

    if(attack_type == "magical") {
        return std::make_unique<MagicalAttack>();
    }
    
    throw custom_exception("invalid input");
}

void Game::remove_enemy_from_map(int enemy_idx) {
    enemy_map[enemies[enemy_idx].get_r()][enemies[enemy_idx].get_c()] = -1;
}

bool Game::battle() {
    int enemy_idx = player_enemy_map_value();
    if(enemy_idx < 0) {
        return false;
    }

    if(!player_has_equipped_item()) {
        std::cout << "INFO: cannot start a battle without equip any item\n";
        std::cout << "(to continue press any key)\n";
        getchar();
        return false;
    }

    enter_alt_terminal();
    set_raw_mode(false);
    unhide_cursor();

    auto continue_press_any_key = []() {
        hide_cursor();
        set_raw_mode(true);
        
        std::cout << "(to continue press any key)\n";
        getchar();

        unhide_cursor();
        set_raw_mode(false);
    };

    auto& e = enemies[enemy_idx];
    bool player_won = true;

    while(!p.is_dead() && !e.is_dead()) {
        render_battle_state(enemy_idx);

        std::cout << "PLAYER:\n";
        try {
            const Item* item = choose_battle_item();
            std::unique_ptr<Attack> attack = choose_battle_attack();
            
            int dealt = 0;
            if(item) {
                int prev_hp = e.get_hp();
                e.take_dmg(item->attack(p, *attack));
                dealt = prev_hp - e.get_hp();
            }

            render_battle_state(enemy_idx);
            std::cout << std::format("PLAYER dealt {} damage to {}\n", dealt, all_toupper(e.get_name()));

            if(e.is_dead()) {
                std::cout << std::format("{} was defeated\n", all_toupper(e.get_name()));
                continue_press_any_key();
                break;
            }

            int defense = 0;
            if(item) {
                defense = item->defense(p, *attack);
            }
            int dealt_enemy = std::max(1, e.get_attack() - defense / 4);
            p.take_dmg(dealt_enemy);
            render_battle_state(enemy_idx);
            std::cout << std::format("{} dealt {} damage to PLAYER\n", all_toupper(e.get_name()), dealt_enemy);
            std::cout << std::format("PLAYER dealt {} damage to {}\n", dealt, all_toupper(e.get_name()));

            if(p.is_dead()) {
                std::cout << "PLAYER lost a battle\n";
                player_won = false;
                continue_press_any_key();
                break;
            }

            continue_press_any_key();
        } catch(const custom_exception& e) {
            if(strcmp(e.what(), "give up") == 0) {
                player_won = false;
                break;
            }

            render_battle_state(enemy_idx);
            std::cout << "ERROR: " << e.what() << '\n';
            continue_press_any_key();
        }
    }

    exit_alt_terminal();
    set_raw_mode(true);
    hide_cursor();

    if(player_won == false) {
        full_clear();
        std::cout << "GAME OVER\n";
        return true;
    }
    
    remove_enemy_from_map(enemy_idx);
    return false;
}

int Game::player_enemy_map_value() {
    return enemy_map[p.get_r()][p.get_c()];
}

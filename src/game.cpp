#include "game.h"
#include "dungeon_builder.h"
#include "equipment_handler.h"
#include "inventory_handler.h"
#include "quit_handler.h"
#include "utils.h"

#include <memory>

Game::Game() : p(Player()) {
    init_handlers();
    DungeonBuilder d(true);
    auto res = d.build();
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
    std::cout << "\n";
    print_instructions();

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
        int idx = enemy_map[p.get_r()][p.get_c()];
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
    if(capabilities.has_items) {
        out << "PICK UP(E) | DROP(G) | ";
    }
    if(capabilities.has_weapons) {
        out << "EQUIP(J) | UNEQUIP(K) | ";
    }
    if(capabilities.has_items || capabilities.has_weapons) {
        out << "GET INFO(I) | ";
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

    /*
    if(input == "gold") {
        int cnt_gold = p.get_gold();
        if(cnt_gold > 0) {
            p.set_gold(cnt_gold - 1);
            cell.add_item(std::make_unique<Gold>());
        }
        
        return;
    } else if(input == "coin") {
        int cnt_coins = p.get_coins();
        if(cnt_coins > 0) {
            p.set_coins(cnt_coins - 1);
            cell.add_item(std::make_unique<Coin>());
        }
        return;
    } else*/if(p.get_inventory().empty() || input == "cancel") {
        return;
    }    

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

    std::cout << "Enter index of weapon from inventory (to cancel write 'cancel'): ";
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

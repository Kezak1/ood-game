#include "game.h"
#include "dungeon_builder.h"
#include "utils.h"

Game::Game() : p(Player()), pos_r(1), pos_c(1) {
    init_actions();
    DungeonBuilder d;
    board = d.build();
    
    /*
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }
    
    const std::vector<std::string> char_board{
        "##########################################",
        "#     ####################           #####",
        "#     #################### ######### #####",
        "### #####                  ######### #####",
        "### #####        #################    ####",
        "###         *    #################    ####",
        "#########        #################    ####",
        "############## ###################*  *####",
        "############## ###########################",
        "############## ###########################",
        "######                              ######",
        "###### ############################ ######",
        "###### ############################ ######",
        "###### ############################ ######",
        "###### ###########        ######### ######",
        "###        #######   *    ######       ###",
        "###        #######        ######       ###",
        "###   *                   ######       ###",
        "###        ######### ###########   *   ###",
        "###### ############# ###########       ###",
        "######               #####################",
        "##########################################",
    };

    std::vector<std::pair<int, int>> items_cords;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            auto& chr = char_board[i][j];
            if(chr == '#') {
                board[i][j] = Cell(true); 
            } else {
                board[i][j] = Cell(false);
                if(chr == '*') {
                    items_cords.push_back({i, j});
                }
            }
        }
    }

    int r1 = items_cords[0].first, c1 = items_cords[0].second;
    board[r1][c1].add_item(std::make_unique<Rock>());
    board[r1][c1].add_item(std::make_unique<Sword>(20, "katana"));
    board[r1][c1].add_item(std::make_unique<Bow>(14, "great bow"));

    int r2 = items_cords[1].first, c2 = items_cords[1].second;
    board[r2][c2].add_item(std::make_unique<OldBook>());
    board[r2][c2].add_item(std::make_unique<StrangeIdol>());

    int r3 = items_cords[2].first, c3 = items_cords[2].second;
    board[r3][c3].add_item(std::make_unique<Axe>(10, "axe"));

    int r4 = items_cords[3].first, c4 = items_cords[3].second;
    board[r4][c4].add_item(std::make_unique<Gold>());
    board[r4][c4].add_item(std::make_unique<Gold>());
    board[r4][c4].add_item(std::make_unique<Gold>());

    int r5 = items_cords[4].first, c5 = items_cords[4].second;
    board[r5][c5].add_item(std::make_unique<Coin>());
    board[r5][c5].add_item(std::make_unique<Coin>());
    board[r5][c5].add_item(std::make_unique<OldBook>());

    int r6 = items_cords[5].first, c6 = items_cords[5].second;
    board[r6][c6].add_item(std::make_unique<Sword>(14, "rapier"));
    */
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

        move_player(k);
        to_start_cursor();
        render_state();
        cur_action_info();

        if(actions.find(k) != actions.end()) {
            if(actions[k]()) {
                break;
            }
        }
    
        to_start_cursor();
        render_state();
        cur_action_info();
       
        std::cout << std::flush;
    }

    unhide_cursor();
    set_raw_mode(false);
}

void Game::init_actions() {
    actions['e'] = [this] {
        player_try_pick_up_item();
        return false;
    };
    actions['g'] = [this] {
        player_try_drop_item();
        return false;
    };
    actions['j'] = [this] {
        player_try_equip_weapon();
        return false;
    };
    actions['k'] = [this] {
        player_try_unequip_weapon();
        return false;
    };
    actions['i'] = [this] {
        player_try_get_item_info();
        return false;
    };
    actions['q'] = [this] {
        return true;
    };
}


void Game::move_player(char c) {
    int new_r = pos_r, new_c = pos_c;
    c = tolower(c);

    switch(c) {
        case 'w':
            new_r--;
            break;
        case 's':
            new_r++;
            break;
        case 'a':
            new_c--;
            break;
        case 'd':
            new_c++;
            break;
        default:
            return;
    }

    if(in_range(new_r, new_c) && !board[new_r][new_c].is_wall()) {
        pos_r = new_r;
        pos_c = new_c;
    }
}

void Game::render_state() {
    print_player_stats();
    print_player_inventory();
    print_player_wallet();
    print_player_hands();

    std::stringstream ss;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(r == pos_r && c == pos_c) {
                ss << C_PLAYER;
                continue;
            }
            if(board[r][c].is_wall()) {
                ss << C_WALL;
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
    auto& items = board[pos_r][pos_c].get_items();
    std::cout << "LOG: ";
    if(items.empty()) {
        std::cout << "standing on empty cell\n";
    } else {
        std::cout << "stading on following items\n";
        int idx = 1;
        std::cout << "[ ";
        for(auto& i : items) {
            std::cout << std::format("{}.({}) ", idx++, i->get_name());
        }
        std::cout << "]\n";
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
    out << "INVENTORY: [ ";
    int idx = 1;
    for(auto& i : inventory) {
        out << std::format("{}.({}) ", idx++, i->get_name());
    }
    out << "]\n";

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

void Game::player_try_pick_up_item() {
    auto& cell = board[pos_r][pos_c];

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

    std::cout << "Enter index of item to drop it from inventory or write 'gold'/'coin' to drop a gold/coin (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();

    if(input == "cancel") {
        return;
    }

    Cell& cell = board[pos_r][pos_c];

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
    } else if(p.get_inventory().empty() || input == "cancel") {
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
            throw std::logic_error("cannot equip this item");
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
            throw std::invalid_argument("invalid input");
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

    std::cout << "Enter index to get info about chose item (to cancel write 'cancel'): ";
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();

    if(input == "cancel") {
        return;
    }

    try {
        int idx = std::stoi(input);
        std::cout << "INFO: " << p.get_item_info(idx) << "\n(to continue press any key)";
        getchar();
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n(to continue press any key)";
        getchar();
    }
}

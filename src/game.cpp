#include "game.h"
#include "utils.h"
#include <memory>


Game::Game() : p(Player()), pos_r(1), pos_c(1) {
    board.resize(ROWS);
    for(auto& row : board) {
        row.resize(COLS);
    }

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1) {
                board[i][j] = Cell(WALL); 
            } else {
                board[i][j] = Cell(EMPTY);
            }
        }
    }

    board[10][10].add_item(std::make_unique<Rock>());
    board[10][10].add_item(std::make_unique<Sword>(10, "katana"));
    board[10][10].add_item(std::make_unique<OldBook>());

    board[15][11].add_item(std::make_unique<Gold>());
    board[12][11].add_item(std::make_unique<Coin>());
}

void Game::main_loop() {
    full_clear();
    hide_cursor();
    set_raw_mode(true);

    render_state();
    cur_action_info();

    while(1) {
        char k = getchar();

        bool flag_break = false;
        bool flag_refresh = false;

        move_player(k);
        to_start_cursor();
        render_state();
        cur_action_info();

        switch(k) {
            case 'q':
                flag_break = true;
                break;
            case 'e':
                player_try_pick_up_item();
                flag_refresh = true;
                break;
            case 'g':
                player_try_drop_item();
                flag_refresh = true;
                break;
            case 'c':
                // player_try_equip_weapon();
                break;
            default:
                break;
        }

        if(flag_refresh) {
            move_player(k);
            to_start_cursor();
            render_state();
            cur_action_info();
        }
        
        if(flag_break) break;

        std::cout << std::flush;
    }

    unhide_cursor();
    set_raw_mode(false);
}

bool in_range(int r, int c) {
    return r >= 0 && c >= 0 && r < ROWS && c < COLS;
}

void Game::move_player(char c) {
    int new_r = pos_r, new_c = pos_c;
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
            return;   std::vector<std::unique_ptr<Item>> items;
    }

    if(in_range(new_r, new_c) && board[new_r][new_c].get_c() == EMPTY) {
        pos_r = new_r;
        pos_c = new_c;
    }
}

void Game::render_state() {
    print_player_stats();
    print_player_inventory();
    print_player_wallet();

    std::stringstream ss;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(r == pos_r && c == pos_c) {
                ss << C_PLAYER;
                continue;
            }
            switch(board[r][c].get_c()) {
                case WALL:
                    ss << C_WALL;
                    break;
                case EMPTY:
                    if(board[r][c].empty()) {
                        ss << C_EMPTY;
                    } else {
                        ss << C_ITEMS;
                    }
                    break;
                default:
                    break;
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
    std::string currency = std::format("COINS: {:<5} | GOLD: {:<5}\n", p.get_coins(), p.get_gold());
    clear_line_cursor();
    std::cout << currency;
}

void Game::print_player_stats() {
    std::string st = std::format(
        "PLAYER: HP {:3}/100 | STR {:2} | DEX {:2} | LCK {:2} | AGR {:2} | WIS {:2}\n",
        p.get_hp(), p.get_str(), p.get_dex(), p.get_lck(), p.get_agr(), p.get_wis(), p.get_gold(), p.get_coins()
    );

    clear_line_cursor();
    std::cout << st;
}

void Game::print_player_inventory() {
    auto& inventory = p.get_inventory();

    std::string inv = "INVENTORY: [ ";
    int idx = 1;
    for(auto& i : inventory) {
        inv += std::format("{}.({}) ", idx++, i->get_name());
    }
    inv += "]\n";

    clear_line_cursor();
    std::cout << inv;
}

void Game::print_player_hands() {
    std::string in = "EQUIPED: ";
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
        if(item->carryable(p)) {
            p.add_item(std::move(item));
        }
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        char _ = getchar();
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

    Cell& cell = board[pos_r][pos_c];

    if(input == "gold") {
        int cnt_gold = p.get_gold();
        if(cnt_gold > 0) {
            p.set_gold(cnt_gold - 1);
            cell.add_item(std::make_unique<Gold>(Gold()));
        }
        
        return;
    } else if(input == "coin") {
        int cnt_coins = p.get_coins();
        if(cnt_coins > 0) {
            p.set_coins(cnt_coins - 1);
            cell.add_item(std::make_unique<Coin>(Coin()));
        }
        return;
    } else if(p.get_inventory().empty() || input == "cancel") {
        return;
    }    

    try {
        int idx = stoi(input);
        cell.add_item(p.take_item(idx));
    } catch(const std::exception& e) {
        std::cout << "ERROR: " << e.what() << '\n' << "(to continue press any key)";
        char _ = getchar();
    }
}

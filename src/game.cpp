#include "game.h"

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

    for(int i = 0; i < 5; i++) {
        auto sth = std::make_unique<Item>("s" + std::to_string(i));
        board[10][10].add_item(std::move(sth));
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
        bool flag_break = false;

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
                break;
            case 'g':
                // player_try_drop_item();
                break;
            case 'c':
                // player_try_equip_weapon();
                break;
            default:
                break;
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
    auto stats = p.get_stats(); 
    auto& inventory = p.get_inventory();

    std::string st = std::format(
        "PLAYER: HP {:3}/100 | STR {:2} | DEX {:2} | LCK {:2} | AGR {:2} | WIS {:2}\n",
        stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], stats[7]
    );
    std::string inv = "INVENTORY: [ ";
    int idx = 1;
    for(auto& i : inventory) {
        inv += std::format("{}.({}) ", idx++, i->get_name());
    }
    inv += "]\n";

    clear_line_cursor();
    std::cout << st;
    clear_line_cursor();
    std::cout << inv;

    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(r == pos_r && c == pos_c) {
                std::cout << C_PLAYER;
                continue;
            }
            switch(board[r][c].get_c()) {
                case WALL:
                    std::cout << C_WALL;
                    break;
                case EMPTY:
                    if(board[r][c].empty()) {
                        std::cout << C_EMPTY;
                    } else {
                        std::cout << C_ITEMS;
                    }
                    break;
                default:
                    break;
            }
        }
        std::cout << '\n';
    }
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

void Game::player_try_pick_up_item() {
    auto& cell = board[pos_r][pos_c];
    if(cell.empty()) {
        return;
    }

    set_raw_mode(false);
    unhide_cursor();

    std::cout << "Enter index which item to pick up (to cancel write 'cancel'): ";
    std::string input;
    int idx = -1;
    std::cin >> input;
    idx = std::atoi(input.c_str());
    
    if(input == "cancel") {
        set_raw_mode(true);
        return;
    }
    

    set_raw_mode(true);
    hide_cursor();

    //TODO FINISH
}
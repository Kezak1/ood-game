#include "console_view.h"
#include "dungeon_builder.h"
#include "game_model.h"
#include "file_logger.h"
#include "player.h"
#include "utils.h"

#include <iostream>
#include <ostream>
#include <termios.h>
#include <unistd.h>
#include <sstream>

namespace {
    inline constexpr auto C_WALL = "█";
    inline constexpr auto C_EMPTY = " ";
    inline constexpr auto C_PLAYER = "¶";
    inline constexpr auto C_ITEMS = "*";
    inline constexpr auto C_ENEMY = "@";
    inline constexpr int MAX_LOG_DISPLAY = 74;

    void full_clear() {
        std::cout << "\033[2J\033[H";
    }

    void full_clear_from_cursor() {
        std::cout << "\033[J";
    }

    void clear_line_cursor() {
        std::cout << "\033[2K";
    }

    void to_start_cursor() {
        std::cout << "\033[H";
    }

    void hide_cursor() {
        std::cout << "\033[?25l";
    }

    void unhide_cursor() {
        std::cout << "\033[?25h";
    }

    void enter_alt_terminal() {
        std::cout << "\033[?1049h";
    }

    void exit_alt_terminal() {
        std::cout << "\033[?1049l";
    }

    void set_raw_mode(bool enable) {
        static termios t;
        static termios raw_t;
        static bool initialized = false;
        
        if(!initialized) {
            tcgetattr(STDIN_FILENO, &t);
            
            raw_t = t;
            raw_t.c_lflag &= ~(ECHO | ICANON);
            initialized = true;
        }
        
        if(enable) {
            tcsetattr(STDIN_FILENO, TCSANOW, &raw_t);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW,&t);
        }
    }
}

ConsoleView::ConsoleView(Logger& l) : logger(l) {
    full_clear();
    hide_cursor();
    set_raw_mode(true);
}

ConsoleView::~ConsoleView() {
    set_raw_mode(false);
    unhide_cursor();
}

void ConsoleView::render_state(const GameModel& model) {
    to_start_cursor();
    print_player_stats(model.player());
    print_player_inventory(model.player());
    print_player_wallet(model.player());
    print_player_hands(model.player());
    print_instructions(model.get_capabilities());
    print_board_with_recent_logs(model);
    print_action_info(model);
}

void ConsoleView::render_battle(const GameModel& model, int enemy_idx) {
    full_clear();
    print_player_stats(model.player());
    print_player_hands(model.player());
    std::cout << '\n';
    print_enemy_hp(model, enemy_idx);
    print_battlefield();
}

char ConsoleView::read_key() {
    return getchar();
}

std::string ConsoleView::ask(const std::string& question) {
    set_raw_mode(false);
    unhide_cursor();

    std::cout << question << std::flush;
    std::string input;
    std::getline(std::cin, input);

    set_raw_mode(true);
    hide_cursor();
    
    return input;
}

void ConsoleView::wait_any_key() {
    std::cout << "(to continue press any key)" << std::endl;
    getchar();
}

void ConsoleView::tell(const std::string& msg) {
    std::cout << msg << std::endl;
}

void ConsoleView::enter_battle_screen() {
    enter_alt_terminal();
    set_raw_mode(false);
    unhide_cursor();
}

void ConsoleView::exit_battle_screen() {
    exit_alt_terminal();
    set_raw_mode(true);
    hide_cursor();
}

void ConsoleView::show_full_log() {
    enter_alt_terminal();
    set_raw_mode(false);
    unhide_cursor();

    std::stringstream ss;

    for(const auto& e : logger.all()) {
        ss << format_log_entry(e) << '\n';
    }
    std::cout << ss.str() << "(to continue press any key)" << std::endl;

    set_raw_mode(true);
    hide_cursor();
    getchar();

    exit_alt_terminal();
}

void ConsoleView::clear() {
    full_clear();
}

void ConsoleView::print_action_info(const GameModel& model) {
    auto& p = model.player();
    auto& board = model.get_board();
    auto& enemies = model.get_enemies();

    full_clear_from_cursor();
    auto& items = board[p.get_r()][p.get_c()].get_items();
    std::cout << "INFO: ";
    if(model.is_enemy_pos(p.get_r(), p.get_c())) {
        int idx = model.player_enemy_map_value();
        std::cout << std::format("{}({}) - hp({}), attack({}), armor({})\n", enemies[idx]->get_name(), enemies[idx]->get_species(), enemies[idx]->get_hp(), enemies[idx]->get_attack(), enemies[idx]->get_arrmor());
    }
    if(items.empty()) {
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

void ConsoleView::print_board_with_recent_logs(const GameModel& model) {
    auto& board = model.get_board();
    auto& p = model.player();
    
    std::cout << "\n";
    const auto logs = logger.recent(8);

    std::stringstream ss;
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            if(board[r][c].is_wall()) {
                ss << C_WALL << C_WALL;
                continue;
            }
            if(r == p.get_r() && c == p.get_c()) {
                ss << C_PLAYER;
            } else if(!board[r][c].no_items()) {
                ss << C_ITEMS;
            } else {
                ss << C_EMPTY;
            }

            if(model.is_enemy_pos(r, c)) {
                ss << C_ENEMY;
            } else {
                ss << C_EMPTY;
            }
        }

        if(r == 0) {
            ss << "   RECENT LOGS";
        } else if(r <= (int)logs.size()) {
            std::string text = format_log_entry(logs[logs.size() - r]);
            if((int)text.size() > MAX_LOG_DISPLAY) {
                text = text.substr(0, MAX_LOG_DISPLAY - 3) + "...";
            }
            ss << "   \033[K" << text;
        }

        ss << '\n';
    }

    std::cout << ss.str();
}

void ConsoleView::print_player_wallet(const Player& p) {
    std::string out = std::format("COINS: {:<5} GOLD: {:<5}\n", p.get_coins(), p.get_gold());
    clear_line_cursor();
    std::cout << out;
}

void ConsoleView::print_player_stats(const Player& p) {
    std::string out = std::format(
        "PLAYER({}): HP {:3}/{:3} | STR {:2} | DEX {:2} | LCK {:2} | AGR {:2} | WIS {:2}\n",
        p.get_name(), p.get_hp(), p.get_max_hp(), p.get_str(), p.get_dex(), p.get_lck(), p.get_agr(), p.get_wis()
    );

    clear_line_cursor();
    std::cout << out;
}

void ConsoleView::print_player_inventory(const Player& p) {
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

void ConsoleView::print_player_hands(const Player& p) {
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

void ConsoleView::print_instructions(const PlayerCapabilities& capabilities) {
    std::stringstream out;
    out << "QUIT(Q) | GET FULL LOG(J) | ";
    if(capabilities.can_move) {
        out << "MOVE(WASD) | ";
    }
    if(capabilities.has_currency && !capabilities.has_items) {
        out << "PICK UP(E) | ";
    }
    if(capabilities.has_items) {
        out << "PICK UP(E) | DROP(G) | EQUIP(K) | UNEQUIP(L) | GET INFO(I) | ";
    }
    if(capabilities.has_enemies) {
        out << "BATTLE(F) | ";
    }
    
    auto strout = out.str();
    strout.pop_back();
    strout.pop_back();

    clear_line_cursor();
    std::cout << strout << std::endl;
}

void ConsoleView::print_battlefield() {
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

void ConsoleView::print_enemy_hp(const GameModel& model, int enemy_idx) {
    auto& e = model.get_enemies()[enemy_idx];
    std::string out = std::format("{}: HP {:3}/{}\n", all_toupper(e->get_name()), e->get_hp(), e->get_max_hp());
    clear_line_cursor();
    std::cout << out;
}

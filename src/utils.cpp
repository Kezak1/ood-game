#include "utils.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <format>
#include <stdexcept>

custom_exception::custom_exception(const char* msg) : msg(msg) {}

const char* custom_exception::what() const noexcept {
    return msg.c_str();
}

int next_random(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(l, r);

    return dist(gen);
}

bool in_range(int r, int c) {
    return r >= 0 && c >= 0 && r < ROWS && c < COLS;
}

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
    static termios old_t;
    if(enable) {
        termios new_t;
        tcgetattr(STDIN_FILENO, &old_t);
    
        new_t = old_t;
        new_t.c_lflag &= ~(ECHO | ICANON);

        tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    }
}

std::string all_toupper(std::string s) {
    for(auto& c : s) {
        c = toupper(c);
    }
    return s;
}

std::string trim(std::string s) {
    auto first = s.find_first_not_of(" \t\r\n");
    if(first == std::string::npos) {
        return "";
    }

    auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
} 

GameConfig load_game_config(const std::filesystem::path& path) {
    std::ifstream input(path);
    if(!input) {
        throw std::runtime_error(std::format("cannot open config file '{}'", path.string()));
    }

    GameConfig config;
    bool has_player_name = false;
    bool has_log_file = false;

    std::string line;
    int line_count = 0;
    
    while(std::getline(input, line)) {
        line_count++;

        std::string cleaned = trim(line);
        if(cleaned.empty() || cleaned[0] == '#') {
            continue;
        }

        auto separator = cleaned.find('=');
        if(separator == std::string::npos) {
            throw std::runtime_error(std::format("valid config line {} (expected key=value)", line_count));
        }

        std::string key = trim(cleaned.substr(0, separator));
        std::string value = trim(cleaned.substr(separator + 1));

        if(key == "player_name") {
            config.player_name = value;
            has_player_name = true;
        } else if(key == "log_file") {
            config.log_file = value;
            has_log_file = true;
        }
    }

    if(!has_player_name || config.player_name.empty()) {
        throw std::runtime_error("config is missing required value: player_name");
    }

    if(!has_log_file || config.log_file.empty()) {
        throw std::runtime_error("config is missing required value: log_file");
    }

    if(config.log_file.is_relative()) {
        auto config_dir = path.parent_path();
        if(!config_dir.empty()) {
            config.log_file = config_dir / config.log_file;
        }
    }

    return config;
}

#pragma once

#include <filesystem>
#include <string>
#include <vector>

class Cell;

class custom_exception : public std::exception {
    std::string msg;
public:
    custom_exception(const char* msg);
    const char* what() const noexcept override;
};

inline constexpr int ROWS = 22;
inline constexpr int COLS = 42;
inline constexpr int MAX_PLAYERS = 9;

bool in_range(int r, int c);

//RIGHT, LEFT, DOWN, UP
inline constexpr int dr[4] = {0, 0, 1, -1};
inline constexpr int dc[4] = {1, -1, 0, 0};

inline constexpr double DEF_MAX = 36.0;
inline constexpr int ENEMY_STAY_CHANGE = 40; // %

int next_random(int l, int r);

std::string all_toupper(std::string s);
std::string trim(std::string s);

struct GameConfig {
    std::string player_name;
    std::filesystem::path log_path;
};

GameConfig load_game_config(const std::filesystem::path& path);

int walkable_dis(const std::vector<std::vector<Cell>>& board, int from_r, int from_c, int to_r, int to_c); 

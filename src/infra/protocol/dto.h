#pragma once

#include <nlohmann/json.hpp>
#include <map>
#include <string>
#include <optional>

class GameModel;
class Logger;

struct ItemDto {
    std::string type;
    std::vector<std::string> modifiers;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ItemDto, type, modifiers)

struct PlayerDto {
    int id;
    std::string name;
    int r, c;
    int hp, max_hp;
    int str, dex, lck, agr, wis;
    int gold, coins;
    std::vector<ItemDto> inventory;
    std::optional<ItemDto> left_hand;
    std::optional<ItemDto> right_hand;
    std::optional<ItemDto> both_hands;
};
void to_json(nlohmann::json& j, const PlayerDto& p);
void from_json(const nlohmann::json& j, PlayerDto& p);

struct EnemyDto {
    std::string name;
    std::string species;
    int r, c;
    int hp, max_hp;
    int atk, armor;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EnemyDto, name, species, r, c, hp, max_hp, atk, armor)

struct CellDto {
    bool wall;
    std::vector<ItemDto> items;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CellDto, wall, items)

struct LogLineDto {
    int idx;
    std::string text;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LogLineDto, idx, text);

struct CapabilitiesDto {
    bool can_move;
    bool has_items;
    bool has_currency;
    bool has_enemies;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CapabilitiesDto, can_move, has_items, has_currency, has_enemies)

struct GameStateDto {
    std::map<int, PlayerDto> players;
    std::vector<EnemyDto> enemies;
    std::vector<std::vector<CellDto>> board;
    std::map<int, int> battles;
    CapabilitiesDto capabilities;
    std::vector<LogLineDto> log_all;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameStateDto, players, enemies, board, battles, capabilities, log_all)

GameStateDto to_dto(const GameModel& model, const Logger& logger);
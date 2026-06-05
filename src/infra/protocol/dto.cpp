#include "dto.h"
#include "item.h"
#include "player.h"
#include "game_model.h"
#include "logger.h"
#include "utils.h"

using nlohmann::json;

namespace {
    ItemDto item_to_dto(const Item& item) {
        return { item.type_label() , item.get_modifiers() };
    }
    std::optional<ItemDto> hand_to_dto(const std::unique_ptr<Item>& hand) {
        if(!hand) {
            return std::nullopt;
        }
        return item_to_dto(*hand);
    }

    PlayerDto player_to_dto(int id, const Player& p) {
        PlayerDto dto;
        dto.id = id;
        dto.name = p.get_name();
        dto.r = p.get_r();
        dto.c = p.get_c();
        dto.hp = p.get_hp();
        dto.max_hp = p.get_max_hp();
        dto.str = p.get_str();
        dto.dex = p.get_dex();
        dto.lck = p.get_lck();
        dto.agr = p.get_agr();
        dto.wis = p.get_wis();
        dto.gold = p.get_gold();
        dto.coins = p.get_coins();

        for(const auto& item : p.get_inventory()) {
            dto.inventory.push_back(item_to_dto(*item));
        }

        dto.left_hand = hand_to_dto(p.get_left_hand());
        dto.right_hand = hand_to_dto(p.get_right_hand());
        dto.both_hands = hand_to_dto(p.get_both_hands());

        return dto;
    }
}

void to_json(json& j, const PlayerDto& p) {
    j = {
        {"id", p.id},
        {"name", p.name},
        {"r", p.r},
        {"c", p.c},
        {"hp", p.hp},
        {"max_hp", p.max_hp},
        {"str", p.str},
        {"dex", p.dex},
        {"lck", p.lck},
        {"agr", p.agr},
        {"wis", p.wis},
        {"gold", p.gold},
        {"coins", p.coins},
        {"inventory", p.inventory},
        {"left_hand", p.left_hand ? json(*p.left_hand) : json(nullptr)},
        {"right_hand", p.right_hand ? json(*p.right_hand) : json(nullptr)},
        {"both_hands", p.both_hands ? json(*p.both_hands) : json(nullptr)},
    };
}

void from_json(const json& j, PlayerDto& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);
    j.at("r").get_to(p.r);
    j.at("c").get_to(p.c);
    j.at("hp").get_to(p.hp);
    j.at("max_hp").get_to(p.max_hp);
    j.at("str").get_to(p.str);
    j.at("dex").get_to(p.dex);
    j.at("lck").get_to(p.lck);
    j.at("agr").get_to(p.agr);
    j.at("wis").get_to(p.wis);
    j.at("gold").get_to(p.gold);
    j.at("coins").get_to(p.coins);
    j.at("inventory").get_to(p.inventory);
    if(!j.at("left_hand").is_null()) {
        p.left_hand = j.at("left_hand").get<ItemDto>();
    }
    if(!j.at("right_hand").is_null()) {
        p.right_hand = j.at("right_hand").get<ItemDto>();
    }
    if(!j.at("both_hands").is_null()) {
        p.both_hands = j.at("both_hands").get<ItemDto>();
    }
}

GameStateDto to_dto(const GameModel& model, const Logger& logger) {
    GameStateDto dto;

    for(const auto& [id, p] : model.get_players()) {
        dto.players[id] = player_to_dto(id, p);
    }

    for(const auto& e : model.get_enemies()) {
        dto.enemies.push_back({
            e->get_name(),
            e->get_species(),
            e->get_r(),
            e->get_c(),
            e->get_hp(),
            e->get_max_hp(),
            e->get_attack(),
            e->get_arrmor()
        });
    }

    dto.board.assign(ROWS, std::vector<CellDto>(COLS));
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            auto& c = model.cell_at(i, j); 

            dto.board[i][j].wall = c.is_wall();
            for(const auto& item : c.get_items()) {
                dto.board[i][j].items.push_back(item_to_dto(*item));
            }
        }
    }

    dto.battles = model.get_battles();
    const auto cap = model.get_capabilities();
    dto.capabilities = {cap.can_move, cap.has_items, cap.has_currency, cap.has_enemies};
    
    const auto& entries = logger.all();
    for(int i = 0; i < (int)entries.size(); i++) {
        dto.log_all.push_back({i, entries[i].msg});
    }

    return dto;
}

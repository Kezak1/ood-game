#include "game_model.h"
#include "dto.h"
#include "dungeon_builder.h"
#include "event.h"
#include "event_bus.h"
#include "utils.h"
#include "player.h"

#include "item.h"
#include "dagger.h"
#include "axe.h"
#include "blaster.h"
#include "black_wand.h"
#include "staff.h"
#include "great_sword.h"
#include "lucky_coin_pouch.h"
#include "coin.h"
#include "gold.h"
#include "metal_fragment.h"
#include "old_book.h"
#include "rock.h"
#include "strange_idol.h"

#include "strong_modifier.h"
#include "mystic_modifier.h"
#include "unlucky_modifier.h"

#include <memory>
#include <stdexcept>
#include <vector>

namespace {
    std::unique_ptr<Item> make_item(const ItemDto& dto) {
        std::unique_ptr<Item> item;

        if(dto.type == "dagger") item = std::make_unique<Dagger>();
        else if(dto.type == "axe") item = std::make_unique<Axe>();
        else if(dto.type == "blaster") item = std::make_unique<Blaster>();
        else if(dto.type == "black_wand") item = std::make_unique<BlackWand>();
        else if(dto.type == "staff") item = std::make_unique<Staff>();
        else if(dto.type == "great_sword") item = std::make_unique<GreatSword>();
        else if(dto.type == "lucky_coin_pouch") item = std::make_unique<LuckyCoinPouch>();
        else if(dto.type == "coin") item = std::make_unique<Coin>();
        else if(dto.type == "gold") item = std::make_unique<Gold>();
        else if(dto.type == "metal_fragment") item = std::make_unique<MetalFragment>();
        else if(dto.type == "old_book") item = std::make_unique<OldBook>();
        else if(dto.type == "rock") item = std::make_unique<Rock>();
        else if(dto.type == "strange_idol") item = std::make_unique<StrangeIdol>();
        else throw std::runtime_error("unknown item type: " + dto.type);

        for(const auto& mod : dto.modifiers) {
            if(mod == "strong") item = std::make_unique<StrongModifier>(std::move(item));
            else if(mod == "mystic") item = std::make_unique<MysticModifier>(std::move(item));
            else if(mod == "unlucky") item = std::make_unique<UnluckyModifier>(std::move(item));
            else throw std::runtime_error("unknown modifier: " + mod);
        }
        return item;
    }

    std::unique_ptr<Enemy> make_enemy(const EnemyDto& dto) {
        return std::make_unique<Enemy>(
            dto.name, dto.r, dto.c, dto.atk, dto.armor, dto.hp, dto.species, nullptr, dto.max_hp
        );
    }
}

GameModel::GameModel(const GameStateDto& dto) : 
    capabilities{dto.capabilities.can_move, dto.capabilities.has_items, 
        dto.capabilities.has_currency, dto.capabilities.has_enemies} 
{
    for(const auto& r : dto.board) {
        std::vector<Cell> a;
        for(const auto& c : r) {
            std::vector<std::unique_ptr<Item>> items;
            for(const auto& i : c.items) {
                items.push_back(make_item(i));
            }
            a.emplace_back(c.wall, std::move(items));
        } 
        board.push_back(std::move(a));
    }

    enemy_map.assign(ROWS, std::vector<int>(COLS, -1));
    int idx = 0;
    for(const auto& edto : dto.enemies) {
        enemies.push_back(make_enemy(edto));
        enemy_map[edto.r][edto.c] = idx++;
    }

    player_map.assign(ROWS, std::vector<int>(COLS, -1));
    for(const auto& [id, pdto] : dto.players) {
        players.emplace(id, Player(pdto.name, pdto.r, pdto.c, pdto.hp, pdto.max_hp, pdto.str, pdto.dex, pdto.lck, pdto.agr, pdto.wis));
        auto& p = players.at(id);
        p.set_gold(pdto.gold);
        p.set_coins(pdto.coins);

        for(const auto& i : pdto.inventory) {
            p.add_item(make_item(i));
        }

        if(pdto.left_hand) {
            p.set_left_hand(make_item(*pdto.left_hand));
        }
        if(pdto.right_hand) {
            p.set_right_hand(make_item(*pdto.right_hand));
        }
        if(pdto.both_hands) {
            p.set_both_hands(make_item(*pdto.both_hands));
        }

        player_map[pdto.r][pdto.c] = id;
    }

    battles = dto.battles;
}

GameModel::GameModel(BuildResult&& res) : 
    enemies(std::move(res.enemies)),
    board(std::move(res.board)),
    capabilities(res.capabilities)
    {
    enemy_map.assign(ROWS, std::vector<int>(COLS, -1));
    int idx = 0;
    for(const auto& e : enemies) {
        enemy_map[e->get_r()][e->get_c()] = idx++;
    }
    player_map.assign(ROWS, std::vector<int>(COLS, -1));
}

void GameModel::player_try_move(int player_id, std::string direction) {
    auto& p = players.at(player_id);

    int i = -1;
    if(direction == "right") {
        i = 0;
    } else if(direction == "left") {
        i = 1;
    } else if(direction == "down") {
        i = 2;
    } else if(direction == "up") {
        i = 3;
    } else {
        throw std::runtime_error("unknown direction");
    }

    int nr = p.get_r() + dr[i];
    int nc = p.get_c() + dc[i];

    if(board[nr][nc].is_wall()) {
        EventBus::instance().publish(WallHitEvent(direction));
        return;
    }
    if(player_map[nr][nc] > 0) {
        //TO DO some event
        return;
    }

    player_map[p.get_r()][p.get_c()] = -1;
    p.set_r(nr);
    p.set_c(nc);
    player_map[p.get_r()][p.get_c()] = player_id;

    EventBus::instance().publish(PlayerMoveEvent(direction));
}

void GameModel::player_try_drop_item(int player_id, int idx) {
    auto& p = players.at(player_id);

    if(p.get_inventory().empty()) {
        return;
    }

    Cell& cell = board[p.get_r()][p.get_c()];
    std::string item_name;

    try {
        if(idx < 1 || idx > (int)p.get_inventory().size()) {
            throw std::out_of_range("invalid index");
        }
        item_name = p.get_inventory()[idx - 1]->get_name();

        cell.add_item(p.take_item(idx));
    } catch(const std::exception& e) {
        EventBus::instance().publish(ActionFailedEvent(e.what()));
        return;
    }

    EventBus::instance().publish(ItemDropEvent(item_name));
}

void GameModel::player_try_pick_up_item(int player_id, int idx) {
    auto& p = players.at(player_id);
    auto& cell = board[p.get_r()][p.get_c()];
    auto& items = cell.get_items();

    std::string item_name;

    if(items.empty()) {
        return;
    }

    try {
        const auto& items = cell.get_items();
        if(idx < 1 || idx > (int)items.size()) {
            throw std::out_of_range("invalid index");
        }
        if(items[idx - 1]->goes_to_inv() && !p.can_add_item()) {
            throw std::runtime_error("inventory is full");
        }
        auto item = cell.take_item(idx);
        item_name = item->get_name();

        int range = item->sound_range();
        if(range > 0) {
            EventBus::instance().publish(SoundEvent{p.get_r(), p.get_c(), range, board});
        }

        if(item->on_pick_up(p)) {
            p.add_item(std::move(item));
        }
    } catch(const std::exception& e) {
        EventBus::instance().publish(ActionFailedEvent(e.what()));
        return;
    }

    EventBus::instance().publish(ItemPickUpEvent(item_name));
}

void GameModel::player_try_equip_item(int player_id, int idx) {
    auto& p = players.at(player_id);
    if(p.get_inventory().empty()) {
        return;
    }

    std::string item_name;

    try {
        std::unique_ptr<Item> item = p.take_item(idx);
        item_name = item->get_name();

        Item* raw_item = item.get();
        item = raw_item->equip(p, std::move(item));
        if(item) {
            p.insert_item(idx, std::move(item), true);
            throw custom_exception("cannot equip this item");
        }
    } catch(const std::exception& e) {
        EventBus::instance().publish(ActionFailedEvent(e.what()));
        return;
    }

    EventBus::instance().publish(ItemEquipEvent(item_name));
}

void GameModel::player_try_unequip_item(int player_id, std::string hand) {
    auto& p = players.at(player_id);
    std::string item_name;
    try {
        if(!p.can_add_item()) {
            throw custom_exception("inventory is full");
        }

        if(hand == "left") {
            auto& left = p.get_left_hand();
            if(!left) {
                return;
            }
            item_name = left->get_name();
            p.add_item(p.take_left_hand());
        } else if(hand == "right") {
            auto& right = p.get_right_hand();
            if(!right) {
                return;
            }
            item_name = right->get_name();
            p.add_item(p.take_right_hand());
        } else if(hand == "both") {
            auto& both = p.get_both_hands();
            if(!both) {
                return;
            }
            item_name = both->get_name();
            p.add_item(p.take_both_hands());
        } else {
            throw custom_exception("invalid input");
        }
    } catch(const std::exception& e) {
        EventBus::instance().publish(ActionFailedEvent(e.what()));
        return;
    }

    EventBus::instance().publish(ItemUnequipEvent(item_name));
}

bool GameModel::player_try_start_battle(int player_id) {
    int enemy_idx = enemy_map_value(player_id);
    if(enemy_idx < 0) {
        return false;
    }

    if(!player_has_equipped_item(player_id)) {
        EventBus::instance().publish(ActionFailedEvent("cannot start battle without equiped item"));
        return false;
    }

    battles[player_id] = enemy_idx;
    EventBus::instance().publish(BattleStartEvent(enemies[enemy_idx]->get_name()));
    return true;
}

RoundResult GameModel::battle_round(int player_id, const Item& item, const Attack& attack) {
    RoundResult res{0, 0, false, false};
    auto& p = players.at(player_id);
    int enemy_idx = battles.at(player_id);
    auto& e = enemies[enemy_idx];

    int prev_hp = e->get_hp();
    e->take_dmg(item.attack(p, attack));
    int dealt = prev_hp - e->get_hp();

    EventBus::instance().publish(AttackEvent("Player", e->get_name(), dealt));

    res.player_dmg_dealt = dealt;

    if(e->is_dead()) {
        EventBus::instance().publish(EnemyDefeatEvent(e->get_name(), e->get_species()));
        res.enemy_died = true;
        end_battle(player_id);
        kill_enemy(enemy_idx);

        return res;
    }

    int defense = item.defense(p, attack);

    dealt = std::max(1, e->get_attack() - defense / 4);
    p.take_dmg(dealt);

    EventBus::instance().publish(AttackEvent(e->get_name(), "Player", dealt)); 

    res.enemy_dmg_dealt = dealt;

    if(p.is_dead()) {
        EventBus::instance().publish(PlayerDefeatEvent(e->get_name()));
        res.player_died = true;
        end_battle(player_id);
    }

    return res;
}

void GameModel::player_give_up(int player_id) {
    int enemy_idx = battles.at(player_id);
    auto& p = players.at(player_id);
    p.take_dmg(p.get_hp());
    end_battle(player_id);
    EventBus::instance().publish(PlayerDefeatEvent(enemies[enemy_idx]->get_name()));
}

bool GameModel::is_player_in_battle(int player_id) const {
    return battles.find(player_id) != battles.end();
}

bool GameModel::is_enemy_in_batlte(int enemy_idx) const {
    for(const auto& [p, e] : battles) {
        if(e == enemy_idx) {
            return true;
        }
    }

    return false;
}

void GameModel::end_battle(int player_id) {
    battles.erase(player_id);
}

bool GameModel::add_player(int player_id, std::string name) {
    if((player_id < 1 || player_id > MAX_PLAYERS) && players.find(player_id) != players.end()) {
        return false;
    }

    auto [r, c] = get_player_starting_pos();
    if(r == -1 && c == -1) {
        return false;
    }
    auto [it, inserted] = players.try_emplace(player_id, name, r, c);
    if(inserted) {
        player_map[r][c] = player_id;
    }
    
    return inserted;
}

bool GameModel::remove_player(int player_id) {
    auto it = players.find(player_id);
    if(it == players.end()) {
        return false;
    }
    
    if(is_player_in_battle(player_id)) {
        end_battle(player_id);
    }
    player_map[it->second.get_r()][it->second.get_c()]   = -1;
    players.erase(it);
    return true;
}

void GameModel::enemies_take_turn() {
    for(int i = 0; i < (int)enemies.size(); i++) {
        auto& e = enemies[i];
        if(e->is_dead() || is_enemy_in_batlte(i) || next_random(1, 100) <= ENEMY_STAY_CHANGE) {
            continue;
        }

        int r = e->get_r(), c = e->get_c();

        std::vector<int> dirs;
        for(int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];

            if(!in_range(nr, nc) || board[nr][nc].is_wall() || enemy_map[nr][nc] >= 0 || (player_map[nr][nc] > 0)) {
                continue;
            }
            dirs.push_back(d);
        }

        if(dirs.empty()) {
            continue;
        }

        int idx = dirs[next_random(0, (int)dirs.size() - 1)];
        int nr = r + dr[idx], nc = c + dc[idx];

        enemy_map[r][c] = -1;
        enemy_map[nr][nc] = i;
        e->set_r(nr);
        e->set_c(nc);
    }
}

void GameModel::kill_enemy(int enemy_idx) {
    auto& e = enemies[enemy_idx];
    enemy_map[e->get_r()][e->get_c()] = -1;

    int last = (int)enemies.size() - 1;
    if(enemy_idx != last) {
        std::swap(enemies[enemy_idx], enemies[last]);
        auto& moved = enemies[enemy_idx];
        enemy_map[moved->get_r()][moved->get_c()] = enemy_idx;
        for(auto& [pid, ei] : battles) {
            if(ei == last) {
                ei = enemy_idx;
            }
        }
    }

    enemies.pop_back();
}

bool GameModel::is_enemy_pos(int r, int c) const {
    return enemy_map[r][c] >= 0;
}

int GameModel::enemy_map_value(int player_id) const {
    return enemy_map[players.at(player_id).get_r()][players.at(player_id).get_c()];
}

int GameModel::player_map_value(int r, int c) const {
    return player_map[r][c];
}

bool GameModel::player_has_equipped_item(int player_id) const {
    return players.at(player_id).get_left_hand() || players.at(player_id).get_right_hand() || players.at(player_id).get_both_hands();
}

Player& GameModel::player(int player_id) {
    return players.at(player_id);
}
const Player& GameModel::player(int player_id) const {
    return players.at(player_id);
}

Cell& GameModel::cell_at(int r, int c) {
    return board[r][c];
}

const Cell& GameModel::cell_at(int r, int c) const {
    return board[r][c];
}

const Enemy& GameModel::get_battled_enemy(int player_id) const {
    return *enemies[battles.at(player_id)];
}

const std::vector<std::vector<Cell>>& GameModel::get_board() const {
    return board;
}

const std::map<int, Player>& GameModel::get_players() const {
    return players;
}

const std::vector<std::unique_ptr<Enemy>>& GameModel::get_enemies() const {
    return enemies;
}

const std::map<int, int>& GameModel::get_battles() const {
    return battles;
}

PlayerCapabilities GameModel::get_capabilities() const {
    return capabilities;
}

std::pair<int, int> GameModel::get_player_starting_pos() {
    std::vector<std::pair<int, int>> a;
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            if(!board[i][j].is_wall() && player_map[i][j] == -1) {
                a.emplace_back(i, j);
            }
        }
    }

    if(a.empty()) {
        return {-1, -1};
    }
    return a[next_random(0, (int)a.size() - 1)];
}
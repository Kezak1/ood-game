#include "game_model.h"
#include "event.h"
#include "event_bus.h"
#include "utils.h"
#include <exception>

GameModel::GameModel(std::string player_name, BuildResult&& res) : 
    p(player_name),
    enemies(std::move(res.enemies)),
    board(std::move(res.board)),
    capabilities(res.capabilities)
    {
    enemy_map.assign(ROWS, std::vector<int>(COLS, -1));
    int idx = 0;
    for(auto& e : enemies) {
        enemy_map[e->get_r()][e->get_c()] = idx++;
    }
}

void GameModel::player_move(int dr, int dc, std::string direction) {
    int nr = p.get_r() + dr;
    int nc = p.get_c() + dc;

    if(board[nr][nc].is_wall()) {
        EventBus::instance().publish(WallHitEvent(direction));
        return;
    }

    p.set_r(nr);
    p.set_c(nc);

    EventBus::instance().publish(PlayerMoveEvent(direction));
}

void GameModel::player_move_up() {
    player_move(-1, 0, "up");
}

void GameModel::player_move_down() {
    player_move(1, 0, "down");
}

void GameModel::player_move_left() {
    player_move(0, -1, "left");
}

void GameModel::player_move_right() {
    player_move(0, 1, "right");
}

void GameModel::player_try_drop_item(int idx) {
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

void GameModel::player_try_pick_up_item(int idx) {
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
            throw custom_exception("inventory is full");
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

void GameModel::player_try_equip_weapon(int idx) {
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

void GameModel::player_try_unequip_weapon(std::string hand) {
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

bool GameModel::check_battle_start(int enemy_idx) {
    if(enemy_idx < 0) {
        return false;
    }

    if(!player_has_equipped_item()) {
        EventBus::instance().publish(ActionFailedEvent("cannot start battle without equiped item"));
        return false;
    }

    EventBus::instance().publish(BattleStartEvent(enemies[enemy_idx]->get_name()));
    return true;
}

RoundResult GameModel::battle_round(int enemy_idx, const Item& item, const Attack& attack) {
    RoundResult res{0, 0, false, false};
    auto& e = enemies[enemy_idx];

    int prev_hp = e->get_hp();
    e->take_dmg(item.attack(p, attack));
    int dealt = prev_hp - e->get_hp();

    EventBus::instance().publish(AttackEvent("Player", e->get_name(), dealt));

    res.player_dmg_dealt = dealt;


    if(e->is_dead()) {
        EventBus::instance().publish(EnemyDefeatEvent(e->get_name(), e->get_species()));
        res.enemy_died = true;

        return res;
    }

    int defense = item.defense(p, attack);

    dealt = std::max(1, e->get_attack() - defense / 4);
    p.take_dmg(dealt);

    EventBus::instance().publish(AttackEvent(e->get_name(), "Player", dealt)); 

    if(p.is_dead()) {
        EventBus::instance().publish(PlayerDefeatEvent(e->get_name()));
        res.player_died = true;
    }

    return res;
}

void GameModel::enemies_take_turn() {
    for(int i = 0; i < (int)enemies.size(); i++) {
        auto& e = enemies[i];
        if(e->is_dead() || next_random(1, 100) <= ENEMY_STAY_CHANGE) {
            continue;
        }

        int r = e->get_r(), c = e->get_c();

        std::vector<int> dirs;
        for(int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];

            if(!in_range(nr, nc) || board[nr][nc].is_wall() || enemy_map[nr][nc] >= 0 || (nr == p.get_r() && nc == p.get_c())) {
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
    }

    enemies.pop_back();
}

bool GameModel::is_enemy_pos(int r, int c) {
    return enemy_map[r][c] >= 0;
}

int GameModel::player_enemy_map_value() {
    return enemy_map[p.get_r()][p.get_c()];
}

bool GameModel::player_has_equipped_item() const {
    return p.get_left_hand() || p.get_right_hand() || p.get_both_hands();
}

Player& GameModel::player() {
    return p;
}
const Player& GameModel::player() const {
    return p;
}

Cell& GameModel::cell_at(int r, int c) {
    return board[r][c];
}

const Cell& GameModel::cell_at(int r, int c) const {
    return board[r][c];
}

const std::vector<std::vector<Cell>>& GameModel::get_board() const {
    return board;
}

const std::vector<std::unique_ptr<Enemy>>& GameModel::get_enemies() const {
    return enemies;
}

PlayerCapabilities GameModel::get_capabilities() const {
    return capabilities;
}
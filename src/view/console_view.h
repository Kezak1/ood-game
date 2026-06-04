#pragma once

#include "game_model.h"
#include "view.h"

#include "logger.h"
#include "dungeon_builder.h"

class ConsoleView : public View {
    Logger& logger;
    bool in_battle_screen = false;
public:
    explicit ConsoleView(Logger& logger);
    ~ConsoleView() override;

    void render(const GameModel& model, int id) override;

    char read_key() override;
    std::string ask(const std::string& question) override;
    void wait_any_key() override;
    void tell(const std::string& msg) override;
    void show_full_log() override;
    void clear() override;
private:
    void render_map(const GameModel& model, int id);
    void render_battle(const GameModel& model, int id);
    void handle_mode_change(bool battle);

    void print_action_info(const GameModel& model, int id);
    void print_player_stats(const Player& p);
    void print_player_wallet(const Player& p);
    void print_player_inventory(const Player& p);
    void print_player_hands(const Player& p);
    void print_board_with_recent_logs(const GameModel& model, int id);
    void print_instructions(const PlayerCapabilities& capabilities);
    void print_battlefield();
    void print_enemy_hp(const Enemy& e); 
};

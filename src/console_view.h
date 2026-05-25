#pragma once

#include "game_model.h"
#include "view.h"

#include "logger.h"
#include "dungeon_builder.h"

class ConsoleView : public View {
    Logger& logger;
public:
    explicit ConsoleView(Logger& logger);
    ~ConsoleView() override;

    void render_state(const GameModel& model) override;
    void render_battle(const GameModel& model, int enemy_idx) override;

    char read_key() override;
    std::string ask(const std::string& question) override;
    void wait_any_key() override;

    void tell(const std::string& msg) override;

    void enter_battle_screen() override;
    void exit_battle_screen() override;

    void show_full_log() override;

    void clear() override;
private:
    void print_action_info(const GameModel& model);
    void print_player_stats(const Player& p);
    void print_player_wallet(const Player& p);
    void print_player_inventory(const Player& p);
    void print_player_hands(const Player& p);
    void print_board_with_recent_logs(const GameModel& model);
    void print_instructions(const PlayerCapabilities& capabilities);
    void print_battlefield();
    void print_enemy_hp(const GameModel& model, int enemy_idx); 
};

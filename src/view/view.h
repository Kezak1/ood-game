#pragma once

#include "game_model.h"

#include <string>

class View {
public:
    virtual ~View() = default;

    virtual void render_state(const GameModel& model) = 0;
    virtual void render_battle(const GameModel& model, int enemy_idx) = 0;

    virtual char read_key() = 0;
    virtual std::string ask(const std::string& question) = 0;
    virtual void wait_any_key() = 0;
    
    virtual void tell(const std::string& msg) = 0;;

    virtual void enter_battle_screen() = 0;
    virtual void exit_battle_screen()  = 0;

    virtual void show_full_log() = 0;

    virtual void clear() = 0;
};

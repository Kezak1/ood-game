#pragma once

#include "dungeon_builder.h"
#include "view.h"

#include <filesystem>

class Game {
public:
    void run_client(std::string ip, std::string port, std::filesystem::path config_path);
    void run_server(int port);
private:
    BuildResult init_dungeon(View& view, Logger& logger);
};
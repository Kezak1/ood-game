#pragma once

#include "dungeon_builder.h"
#include "view.h"

#include <filesystem>

class Game {
public:
    void run(std::filesystem::path config_path);
private:
    BuildResult init_dungeon(View& view, Logger& logger);
};
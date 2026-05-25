#pragma once

#include "console_view.h"
#include "controller.h"
#include "dungeon_builder.h"
#include "event_bus.h"
#include "log_event_visitor.h"
#include "file_logger.h"
#include "utils.h"
#include "library_theme_factory.h"
#include "metal_theme_factory.h"
#include "vault_theme_factory.h"

#include <exception>
#include <filesystem>
#include <iostream>

class Game {
public:
    void run(std::filesystem::path config_path);
private:
    BuildResult init_dungeon(View& view, Logger& logger);
};
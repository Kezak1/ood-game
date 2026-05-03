#include "game.h"
#include "event_bus.h"
#include "log_event_visitor.h"
#include "file_logger.h"
#include "utils.h"

#include <exception>
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        std::filesystem::path config_path = "config.ini";
        if(argc > 1) {
            config_path = argv[1];
        }

        GameConfig config = load_game_config(config_path);
        
        FileLogger logger(config.log_file, config.player_name);
        LogEventVisitor event_logger(logger);

        EventBus::instance().subscribe(event_logger);

        Game g(logger, config.player_name, config.log_file);
        g.main_loop();
    } catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
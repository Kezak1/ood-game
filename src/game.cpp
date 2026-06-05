#include "game.h"

#include "game_model.h"
#include "console_view.h"
#include "event_bus.h"
#include "log_event_visitor.h"
#include "file_logger.h"
#include "utils.h"
#include "library_theme_factory.h"
#include "metal_theme_factory.h"
#include "vault_theme_factory.h"
#include "game_server.h"
#include "client_controller.h"

#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>

BuildResult Game::init_dungeon(View& view, Logger& logger) {
    std::stringstream ss;
    ss << "1. Library theme\n";
    ss << "2. Metal theme\n";
    ss << "3. Vault theme\n\n";
    ss << "Choose board theme: ";
    std::string input = trim(view.ask(ss.str()));

    DungeonBuilder d(true);
    BuildResult res;

    if(input == "1") {
        LibraryThemeFactory lt;
        res = d.build(lt, logger);
    } else if(input == "2") {
        MetalThemeFactory mt;
        res = d.build(mt, logger);
    } else if(input == "3") {
        VaultThemeFactory vt;
        res = d.build(vt, logger);
    } else {
        throw std::runtime_error("invalid theme choice");
    }

    view.tell(res.begining_msg);
    view.wait_any_key();

    return res;
}

void Game::run_client(std::string ip, std::string port, std::filesystem::path config_path) {
    try {
        GameConfig config = load_game_config(config_path);
        
        FileLogger logger(config.log_path, config.player_name);
        LogEventVisitor event_logger(logger);

        EventBus::instance().subscribe(event_logger);
        
        ConsoleView view(logger);
        
        ClientController c(view, logger, config.player_name, logger.get_path(), ip, port);
        c.loop();
    } catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

void Game::run_server(int port) {
    try {
        FileLogger logger("server_logs", "server");
        LogEventVisitor event_logger(logger);

        EventBus::instance().subscribe(event_logger);
        
        ConsoleView view(logger);
        GameModel model(init_dungeon(view, logger));
        
        GameServer sv(model, logger, port);
        sv.run();
    } catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}
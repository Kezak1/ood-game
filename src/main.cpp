#include "game.h"

#include <cstdlib>
#include <filesystem>

int main(int argc, char* argv[]) {
    std::filesystem::path config_path = "config.ini";
    if(argc > 1) {
        config_path = argv[1];
    }

    Game g;
    g.run(config_path);

    return EXIT_SUCCESS;
}
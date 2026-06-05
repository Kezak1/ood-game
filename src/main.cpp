#include "game.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

[[noreturn]] void usage(std::string name) {
    std::cerr << std::format("USAGE: {} <mode> <options>\n", name);
    std::exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    Game g;
    if(argc >= 2 && std::string(argv[1]) == "--server") {
        int port = 5555;
        if(argc >= 3) {
            port = std::stoi(argv[2]);
        }
        
        g.run_server(port);
    } else if(argc >= 2 && std::string(argv[1]) == "--client") {
        std::string ip = "127.0.0.1", port = "5555";
        if(argc >= 3) {
            std::string a = argv[2];
            auto colon = a.find(':');
            if(colon != std::string::npos) {
                ip = a.substr(0, colon); 
                port = a.substr(colon + 1);
            } else {
                ip = a;
            }
        }
        g.run_client(ip, port, "config.ini");
    } else {
        usage(std::string(argv[0]));
    }

    return EXIT_SUCCESS;
}
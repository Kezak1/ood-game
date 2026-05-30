#include "game.h"
#include "tcp_server.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

void tcp_test() {
    TcpServer server(5555);

    server.on_connect = [&](int fd) {
        std::cout << "client " << fd << " connected\n";
        server.send(fd, "welcome " + std::to_string(fd) + "\n");
    };

    server.on_message = [&](int fd, std::string msg) {
        std::cout << "[" << fd << "] " << msg << "\n";
        server.broadcast(std::to_string(fd) + ": " + msg + "\n");
    };

    server.on_disconnect = [&](int fd) {
        std::cout << "client " << fd << " disconnected\n";
    };

    std::cout << "listening\n";
    server.run();
    std::cout << "server stopped\n";
}

int main(int argc, char* argv[]) {
    std::filesystem::path config_path = "config.ini";
    if(argc > 1) {
        config_path = argv[1];
    }

    Game g;
    g.run(config_path);
    // tcp_test();

    return EXIT_SUCCESS;
}
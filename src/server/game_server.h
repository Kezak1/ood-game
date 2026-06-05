#pragma once

#include "tcp_server.h"

#include <map>
#include <stack>
#include <string>

class GameModel;
class Logger;

class GameServer {
    GameModel& model;
    Logger& logger;
    TcpServer server;

    std::stack<int> free_ids;
    std::map<int, int> fd_to_id;

    static constexpr int MAX_PLAYERS = 9;
public:
    GameServer(GameModel& model, Logger& logger, int port);
    void run();
private:
    void handle_connect(int fd);
    void handle_message(int fd, std::string msg);
    void handle_disconnect(int fd);
    void handle_join(int fd, std::string name);

    void broadcast_state();
    int get_id(int fd) const;
};

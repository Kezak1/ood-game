#pragma once

#include "tcp_client.h"
#include "action_handler.h"
#include "dto.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

class View;
class Logger;
class GameModel;
class Command;
struct GameStateDto;

class ClientController {
    View& view;
    Logger& logger;
    TcpClient tcp_client;

    std::string player_name;
    std::filesystem::path log_path;

    std::unique_ptr<GameModel> model;
    std::optional<GameStateDto> model_dto;
    
    int id = -1;
    int last_log_idx = -1;
    int epoll_fd = -1;
    bool do_work = true;

    std::vector<std::unique_ptr<ActionHandler>> handlers;
public:
    ~ClientController();
    ClientController(View& view, Logger& logger, std::string player_name, std::filesystem::path log_path, std::string ip, std::string port);
    void loop();
private:
    void init_handlers();
    void handle_stdin();
    void apply_message(const std::string& line);
    void apply_state(const GameStateDto& dto);
    void send_command(const Command& cmd);
    void await_state();
    void run_battle();
};
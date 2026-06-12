#include "game_server.h"

#include "game_model.h"
#include "logger.h"
#include "command.h"
#include "dto.h"

#include <exception>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

GameServer::GameServer(GameModel& model, Logger& logger, int port) :
    model(model), logger(logger), server(port) 
{
    for(int i = MAX_PLAYERS; i >= 1; i--) {
        free_ids.push(i);
    }
}

void GameServer::run() {
    server.on_connect = [this](int fd) {
        handle_connect(fd);
    };
    server.on_message = [this](int fd, std::string msg) {
        handle_message(fd, std::move(msg));
    };
    server.on_disconnect = [this](int fd) {
        handle_disconnect(fd);
    };

    std::cout << "server listening\n";
    server.run();
}

void GameServer::handle_connect(int fd) {
    std::cout << "connection on fd " << fd << ", awaiting join\n";
}

void GameServer::handle_message(int fd, std::string msg) {
    json j;
    try {
        j = json::parse(msg);
    } catch(const std::exception& e) {
        std::cerr << "bad json from fd " << fd << ": " << e.what() << '\n';
        return;
    }

    int id = get_id(fd);

    if(id < 0) {
        if(j.value("type", "") == "join") {
            handle_join(fd, j.value("name", "player"));
        }
        return;
    }

    try {
        auto cmd = Command::from_json(j);
        cmd->execute(model, id);
        model.enemies_take_turn();
    } catch(const std::exception& e) {
        std::cerr << "dropped bad message: " << e.what() << '\n';
    }
    broadcast_state();
}

void GameServer::handle_disconnect(int fd) {
    int id = get_id(fd);
    if(id < 0) {
        return;
    }

    model.remove_player(id);
    free_ids.push(id);
    fd_to_id.erase(fd);

    broadcast_state();
    std::cout << "player " << id << " left\n";
}

void GameServer::handle_join(int fd, std::string name) {
    if(free_ids.empty()) {
        return;
    }
    int id = free_ids.top();
    if(!model.add_player(id, name)) {
        return;
    }
    free_ids.pop();
    fd_to_id[fd] = id;

    json hello = {
        {"type", "hello"},
        {"id", id}
    };
    server.send(fd, hello.dump() + "\n");

    broadcast_state();
    std::cout << name << " joined as a player " << id << '\n';
}

void GameServer::broadcast_state() {
    GameStateDto dto = to_dto(model, logger);
    json j = dto;
    server.broadcast(j.dump() + "\n");
}

int GameServer::get_id(int fd) const {
    auto it = fd_to_id.find(fd);
    if(it == fd_to_id.end()) {
        return -1;
    }
    return it->second;
}
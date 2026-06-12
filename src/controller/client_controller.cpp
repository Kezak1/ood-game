#include "client_controller.h"

#include "action_handler.h"
#include "game_model.h"
#include "player.h"
#include "tcp_client.h"
#include "view.h"
#include "logger.h"
#include "command.h"
#include "dto.h"
#include "event.h"
#include "event_bus.h"

#include "quit_handler.h"
#include "move_handler.h"
#include "equipment_handler.h"
#include "inventory_handler.h"
#include "battle_handler.h"
#include "view_log_handler.h"
#include "net_utils.h"

#include <cctype>
#include <cerrno>
#include <exception>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <sys/epoll.h>
#include <unistd.h>

using nlohmann::json;

inline constexpr auto MAX_EVENTS = 16;

namespace {
    std::string auto_choose_hand(const Player& p) {
        if(p.get_both_hands()) {
            return "both";
        }
        if(p.get_left_hand() && !p.get_right_hand()) {
            return "left";
        }
        if(!p.get_left_hand() && p.get_right_hand()) {
            return "right";
        }
        return "";
    }

    void add_to_epoll(int epoll_fd, int fd) {
        struct epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = fd;
        if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            ERR("epoll_ctl");
        }
    }
}

ClientController::~ClientController() {
    if(epoll_fd >= 0) {
        close(epoll_fd);
    }
}

ClientController::ClientController(View& view, Logger& logger, std::string player_name, std::filesystem::path log_path, std::string ip, std::string port) :
    view(view), logger(logger), tcp_client(ip, port), player_name(player_name), log_path(log_path)
{
    init_handlers();
}

void ClientController::loop() {
    tcp_client.on_message = [this](const std::string& line) {
        apply_message(line);
    };

    int epoll_fd = epoll_create1(0);
    if(epoll_fd < 0) {
        ERR("epoll_create1");
    }
    add_to_epoll(epoll_fd, STDIN_FILENO);
    add_to_epoll(epoll_fd, tcp_client.get_fd());

    json json_join = {
        {"type", "join"},
        {"name", player_name}
    };
    tcp_client.send(json_join.dump() + "\n");
    
    epoll_event events[MAX_EVENTS];
    
    view.clear();
    while(do_work) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if(nfds < 0) {
            if(errno == EINTR) {
                continue;
            }
            break;
        }

        for(int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;

            if(fd == tcp_client.get_fd()) {
                model_dto.reset();
                if(!tcp_client.read_available()) {
                    do_work = false;
                    break;
                }
                if(model_dto) {
                    apply_state(*model_dto);
                }
            } else if(fd == STDIN_FILENO) {
                handle_stdin();
            }
        }

        if(model && id >= 0 && model->player(id).is_dead()) {
            break;
        }
    }

    if(model && id >= 0 && model->player(id).is_dead()) {
        view.clear();
        view.tell("GAME OVER\nLOG FILE: " + log_path.string());
    }
}

void ClientController::handle_stdin() {
    if(!model || id < 0) {
        view.read_key();
        return;
    }
    char k = std::tolower(view.read_key());

    if(model->is_player_in_battle(id)) {
        handle_battle_key(k);
        return;
    }
    
    HandleResult res;
    
    for(auto& h : handlers) {
        res = h->handle(*model, id, view, k);
        if(res.handled) {
            break;
        }
    }

    if(!res.handled) {
        EventBus::instance().publish(UnknownKeyEvent(k));
        view.render(*model, id);
    } else {
        if(res.cmd) {
            send_command(*res.cmd);
        } else {
            view.render(*model, id);
        }
        if(res.quit) {
            do_work = false;
        }
    }
}

void ClientController::apply_message(const std::string& msg) {
    try {
        json j = json::parse(msg);
        if(j.value("type", "") == "hello") {
            id = j.at("id");
            return;
        }
        model_dto = j.get<GameStateDto>();
    } catch(const std::exception& e) {
        std::cerr << "bad message: " << e.what() << '\n';
    }
}

void ClientController::apply_state(const GameStateDto& dto) {
    for(const auto& entry : dto.log_all) {
        if(entry.idx > last_log_idx) {
            logger.log(entry.text);
            last_log_idx = entry.idx;
        }
    }
    model = std::make_unique<GameModel>(dto);
    if(id >= 0) {
        redraw_battle();
    }
}

void ClientController::send_command(const Command& cmd) {
    tcp_client.send(cmd.to_json().dump() + "\n");
}

void ClientController::handle_battle_key(char k) {
    if(k == 'g') {
        send_command(GiveUpCommand());
        pending_hand.reset();
        return;
    }

    if(!pending_hand) {
        std::string hand = auto_choose_hand(model->player(id));
        if(!hand.empty()) {
            pending_hand = hand;
        } else {
            switch(k) {
                case 'l':
                    pending_hand = "left";
                    break;
                case 'r':
                    pending_hand = "right";
                    break;
                case 'b':
                    pending_hand = "both";
                    break;                    
            }
            redraw_battle();
            return;
        }
    }

    std::string attack;
    switch(k) {
        case 'n':
            attack = "normal";
            break;
        case 's':
            attack = "stealth";
            break;
        case 'm':
            attack = "magical";
            break;
        default:
            redraw_battle();
            break;
    }

    send_command(BattleRoundCommand(*pending_hand, attack));
    pending_hand.reset();
}

void ClientController::redraw_battle() {
    if(!model || id < 0) {
        return;
    }

    if(!model->is_player_in_battle(id)) {
        pending_hand.reset();
    }

    view.render(*model, id);
    if(model->is_player_in_battle(id)) {
        if(!pending_hand && auto_choose_hand(model->player(id)).empty()) {
            view.tell("hand: (l)eft | (r)ight | (b)oth | (g)ive up");
        } else {
            view.tell("attack: (n)ormal | (s)tealth | (m)agical | (g)ive up");
        }
    }
}

void ClientController::init_handlers() {
    handlers.clear();
    handlers.push_back(std::make_unique<QuitHandler>());
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<EquipmentHandler>());
    handlers.push_back(std::make_unique<InventoryHandler>());
    handlers.push_back(std::make_unique<BattleHandler>());
    handlers.push_back(std::make_unique<ViewLogHandler>());
}

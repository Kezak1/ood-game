#pragma once

#include <map>
#include <string>
#include <functional>

struct ClientState;

class TcpServer {
    int listen_fd = -1;
    int epoll_fd = -1;

    std::map<int, std::string> clients;

    static constexpr auto MAX_CLIENTS = 9;
public:
    ~TcpServer();
    explicit TcpServer(int port);
    TcpServer(const TcpServer&) = delete;
    TcpServer& operator=(const TcpServer&) = delete;

    void run();
    void stop();

    void send(int fd, const std::string& msg);
    void broadcast(const std::string& msg);

    std::function<void(int fd)> on_connect;
    std::function<void(int fd, std::string)> on_message;
    std::function<void(int fd)> on_disconnect;
private:
    void add_client(int fd);
    void remove_client(int fd);
    void handle_client(int fd);
};

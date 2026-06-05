#pragma once

#include <functional>
#include <string>

class TcpClient {
    int fd = -1;
    std::string read_buf;
public:
    ~TcpClient();
    TcpClient(const std::string& ip, const std::string& port);
    TcpClient(const TcpClient&) = delete;
    TcpClient& operator=(const TcpClient&) = delete;

    const int& get_fd() const;

    void send(const std::string& line);
    bool read_available();

    std::function<void(const std::string&)> on_message;
};
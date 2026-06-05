#include "tcp_client.h"
#include "net_utils.h"

#include <sys/types.h>
#include <unistd.h>

inline constexpr auto MSG_SIZE = 4096;

TcpClient::~TcpClient() {
    if(fd >= 0) {
        close(fd);
    }
}

TcpClient::TcpClient(const std::string& ip, const std::string& port) {
    fd = connect_tcp_socket(ip.c_str(), port.c_str());
}

const int& TcpClient::get_fd() const {
    return fd;
}

void TcpClient::send(const std::string& msg) {
    ssize_t sent = 0;
    while(sent < (ssize_t)msg.size()) {
        ssize_t n = TEMP_FAILURE_RETRY(write(fd, msg.data() + sent, msg.size() - sent));
        if(n <= 0) {
            ERR("write");
        }
        sent += n;
    }
}

bool TcpClient::read_available() {
    char buf[MSG_SIZE];
    ssize_t n = TEMP_FAILURE_RETRY(read(fd, buf, sizeof(buf)));
    if(n <= 0) {
        return false;
    }
    read_buf.append(buf, n);

    size_t pos;
    while((pos = read_buf.find('\n')) != std::string::npos) {
        std::string line = read_buf.substr(0, pos);
        read_buf.erase(0, pos + 1);
        if(!line.empty() && on_message) {
            on_message(line);
        }
    }
    return true;
}
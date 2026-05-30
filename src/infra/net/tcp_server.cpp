#include "tcp_server.h"
#include "net_utils.h"

#include <csignal>
#include <cerrno>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <atomic>
#include <vector>

inline constexpr auto MAX_EVENTS = 16; 
inline constexpr auto MSG_SIZE = 4096;

namespace {
    std::atomic<bool> do_work{false};

    void sigint_handler(int signo) {
        (void)signo;
        do_work = false;
    }

    void set_nonblock(int fd) {
        int flags = fcntl(fd, F_GETFL) | O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);
    }

    void add_to_epoll(int epoll_fd, int fd) {
        struct epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = fd;
        if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            ERR("epoll_ctl");
        }
    }

    void delete_from_epoll(int epoll_fd, int client_fd) {
        if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL) == -1) {
            ERR("epoll_ctl");
        }
    }
}

TcpServer::TcpServer(int port) {
    if(sethandler(SIG_IGN, SIGPIPE)) {
        ERR("sethandler");
    }
    if(sethandler(sigint_handler, SIGINT)) {
        ERR("sethandler");
    }

    listen_fd = bind_tcp_socket(port, 15);
    set_nonblock(listen_fd);

    epoll_fd = epoll_create1(0);
    if(epoll_fd < 0) {
        ERR("epoll_create1");
    }

    add_to_epoll(epoll_fd, listen_fd);
}

TcpServer::~TcpServer() {
    for(auto& [fd, s] : clients) {
        close(fd);
    }
    close(listen_fd);
    close(epoll_fd);
}

void TcpServer::run() {
    do_work = true;
    epoll_event events[MAX_EVENTS];

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    while(do_work) {
        int nfds = epoll_pwait(epoll_fd, events, MAX_EVENTS, -1, &oldmask);
        if(nfds < 0) {
            if(errno == EINTR) {
                continue;
            }
            ERR("epoll_pwait");
        }

        for(int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;
            if(listen_fd == fd) {
                int client_fd = add_new_client(listen_fd);
                if(client_fd < 0) {
                    continue;
                }
                add_client(client_fd);
            } else {
                handle_client(fd);
            }
        }
    }

    sigprocmask(SIG_UNBLOCK, &mask, NULL);
}

void TcpServer::stop() {
    do_work = false;
}

void TcpServer::send(int fd, const std::string& msg) {
    if(clients.find(fd) == clients.end()) {
        return;
    }

    ssize_t n = TEMP_FAILURE_RETRY(write(fd, msg.data(), msg.size()));
    if(n < 0) {
        if(errno == EPIPE || errno == ECONNRESET) {
            remove_client(fd);
            return;
        }
    }
}

void TcpServer::broadcast(const std::string& msg) {
    std::vector<int> fds;
    fds.reserve(clients.size());
    for(auto& [fd, buf] : clients) {
        fds.push_back(fd);
    }
    for(int fd : fds) {
        send(fd, msg);
    }
}

void TcpServer::add_client(int fd) {
    if(clients.size() >= MAX_CLIENTS) {
        close(fd);
        return;
    }

    set_nonblock(fd);
    add_to_epoll(epoll_fd, fd);

    clients[fd] = "";
    if(on_connect) on_connect(fd);
}

void TcpServer::remove_client(int fd) {
    delete_from_epoll(epoll_fd, fd);
    close(fd);
    if(on_disconnect) on_disconnect(fd);
    clients.erase(fd);
}

void TcpServer::handle_client(int fd) {
    auto it = clients.find(fd);
    if(it == clients.end()) {
        return;
    }
    std::string& read_buf = it->second;

    char buf[MSG_SIZE];
    ssize_t n = TEMP_FAILURE_RETRY(read(fd, buf, sizeof(buf)));
    if(n > 0) {
        read_buf.append(buf, n);
    } else if(n == 0) {
        remove_client(fd);
        return;
    } else {
        if(errno != EAGAIN && errno != EWOULDBLOCK) {
            remove_client(fd);
            return;
        }
    }

    std::vector<std::string> msgs;
    size_t pos;

    while((pos = read_buf.find('\n')) != std::string::npos) {
        msgs.emplace_back(read_buf, 0, pos);
        read_buf.erase(0, pos + 1);
    }

    for(auto& m : msgs) {
        if(!m.empty() && m.back() == '\r') {
            m.pop_back();
        }
        if(on_message) on_message(fd, std::move(m));
    }
}
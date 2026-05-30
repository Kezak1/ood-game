#pragma once

#include <cerrno>
#include <source_location>
#include <netinet/in.h>
#include <cstdint>

#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(expression)             \
    (__extension__({                               \
        long int __result;                         \
        do                                         \
            __result = (long int)(expression);     \
        while (__result == -1L && errno == EINTR); \
        __result;                                  \
    }))
#endif

#define ERR(msg) throw_errno(msg)

[[noreturn]] void throw_errno(const char* what, std::source_location loc = std::source_location::current());
int sethandler(void (*f)(int), int sigNo);
int make_tcp_socket(void);
sockaddr_in make_address(const char *address, const char *port);
int connect_tcp_socket(const char *name, const char *port);
int bind_tcp_socket(uint16_t port, int backlog_size);
int add_new_client(int sfd);
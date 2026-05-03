#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

struct LogEntry {
    std::chrono::system_clock::time_point time;
    std::string msg;
};

class Logger {
public:
    virtual ~Logger() = default;

    virtual void log(std::string msg) = 0;
    virtual std::vector<LogEntry> recent(int count) const = 0;
    virtual const std::vector<LogEntry>& all() const = 0;
};

#endif

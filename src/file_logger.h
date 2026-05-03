#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "logger.h"

class FileLogger : public Logger {
    std::vector<LogEntry> entries;
    std::filesystem::path path;
    std::ofstream file;
public:
    FileLogger(std::filesystem::path dir, std::string player_name);

    void log(std::string msg) override;
    std::vector<LogEntry> recent(int count) const override;
    const std::vector<LogEntry>& all() const override;
    const std::filesystem::path& get_path() const;
};

std::string format_log_entry(const LogEntry& entry);

#endif

#include "file_logger.h"
#include "logger.h"

#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>
#include <format>
#include <algorithm>

std::string timestamp_for_file() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d_%H-%M-%S");
    
    return ss.str();
}

std::string format_log_entry(const LogEntry& entry) {
    std::time_t t = std::chrono::system_clock::to_time_t(entry.time);

    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&t), "%Y-%m-%d_%H-%M-%S") << "] " << entry.msg;

    return ss.str();
}

std::filesystem::path prepare_log_file(const std::filesystem::path& path) {
    const auto parent = path.parent_path();
    if(!parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    return path;
}

/*
std::filesystem::path make_unique_path(const std::filesystem::path& dir, const std::string& player_name) {
    std::filesystem::create_directories(dir);
    
    std::string base = player_name + "_" + timestamp_for_file();
    std::filesystem::path path = dir / (base + ".log");
    
    int suffix = 1;
    while(std::filesystem::exists(path)) {
        path = dir / std::format("{}_{}.log", base, suffix);
        suffix++;
    }

    return path;
}
*/

FileLogger::FileLogger(std::filesystem::path file_path, std::string player_name) : path(prepare_log_file(file_path)), file(path, std::ios::app) {
    if(!file) {
        throw std::runtime_error(std::format("cannot open log file '{}'", path.string()));
    }
    file << "===================================================================================================\n";
    log(std::format("Game started - player_name: {}", player_name));
}

void FileLogger::log(std::string msg) {
    LogEntry entry {
        std::chrono::system_clock::now(),
        msg
    };
    
    entries.push_back(entry);
    file << format_log_entry(entry) << std::endl;
}

std::vector<LogEntry> FileLogger::recent(int count) const {
    int start = std::max(0, (int)entries.size() - count);
    return {entries.begin() + start, entries.end()};
}

const std::vector<LogEntry>& FileLogger::all() const {
    return entries;
}

std::filesystem::path FileLogger::file_path() const {
    return path;
}
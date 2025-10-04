#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger
{
public:
    static void init();

    template<typename... Args>
    static void info(Args&&... args);

    template<typename... Args>
    static void error(Args&&... args);

private:
    static std::shared_ptr<spdlog::logger> _logger;
};

template <typename... Args>
inline void Logger::info(Args &&...args)
{
    _logger->info(std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::error(Args &&...args)
{
    _logger->error(std::forward<Args>(args)...);
}

#include "logger.h"

std::shared_ptr<spdlog::logger> Logger::_logger;

void Logger::init()
{
    _logger = spdlog::stdout_color_mt("console");
    _logger->set_level(spdlog::level::trace);
    _logger->set_pattern("[%T] [%^%l%$] %v");

    info("Logger initialized");
}
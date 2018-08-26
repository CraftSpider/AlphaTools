
#include <stdexcept>
#include "logger.h"

namespace logging {

Logger::Logger() {
    this->name = "NULL";
    level = Level::NO_LEVEL;
    handlers = std::vector<Handler*>();
}

Logger::Logger(const std::string &name) : Logger() {
    this->name = name;
}

Level Logger::get_effective_level() {
    if (level == Level::NO_LEVEL) {
        return parent->get_effective_level();
    }
    return level;
}

void Logger::set_level(const Level &level) {
    if (name == "root" && level == Level::NO_LEVEL) {
        throw std::runtime_error("Root logger cannot have NO_LEVEL");
    }
    this->level = level;
}

void Logger::set_parent(Logger* parent) {
    this->parent = parent;
}

void Logger::log(const std::string &message, const Level &level) {
    if (level >= get_effective_level()) {
        for (auto handler : handlers) {
            handler->log(message, level);
        }
    }
}

void Logger::trace(const std::string &message) {
    log(message, Level::TRACE);
}

void Logger::debug(const std::string &message) {
    log(message, Level::DEBUG);
}

void Logger::info(const std::string &message) {
    log(message, Level::INFO);
}

void Logger::warn(const std::string &message) {
    log(message, Level::WARN);
}

void Logger::error(const std::string &message) {
    log(message, Level::ERROR);
}

void Logger::fatal(const std::string &message) {
    log(message, Level::FATAL);
}

void Logger::add_handler(Handler *handler) {
    handlers.push_back(handler);
}

bool Logger::remove_handler(Handler *handler) {
    for (uint i = 0; i < handlers.size(); ++i) {
        if (handlers[i] == handler) {
            handlers.erase(handlers.begin() + i);
            return true;
        }
    }
    return false;
}

}

#include <stdexcept>
#include <sstream>
#include <cctype>
#include "logging/logger.h"

namespace logging {

Logger::Logger() {
    this->name = "NULL";
    level = NO_LEVEL;
    stream_level = AT_DEFAULT_LOGGER_LEVEL;
    handlers = std::vector<Handler*>();
}

Logger::Logger(const std::string &name) : Logger() {
    this->name = name;
}

Logger& Logger::operator<<(Level* level) {
    stream_level = level;
    return *this;
}

Logger& Logger::operator<<(const std::string& input) {
    this->log(input, stream_level);
    return *this;
}

Level* Logger::get_effective_level() const {
    if (level == NO_LEVEL) {
        return parent->get_effective_level();
    }
    return level;
}

std::string Logger::get_effective_pattern() const {
    if (pattern.empty()) {
        return parent->get_effective_pattern();
    }
    return pattern;
}

std::string Logger::format_instruct(const std::string &instruct, std::string message, const Level* level) {
    (void)pattern; // TODO: use the logger pattern
    std::stringstream out;
    if (instruct[0] == 'l') {
        out << (std::string)*level;
    } else if (instruct[0] == 'm') {
        out << message;
    } else {
        throw std::runtime_error("Unrecognized log format instruction");
    }
    return out.str();
}

std::string Logger::log_format(const std::string &message, const Level* level) {
    bool escaped = false, in_pat = false;
    std::stringstream out;
    std::string instruct, pattern = get_effective_pattern();
    for (char c : pattern) {
        if (escaped) {
            out << c;
        } else if (in_pat) {
            if (!std::isalnum(c)) {
                out << format_instruct(instruct, message, level);
                instruct = "";
                if (c != '%') {
                    in_pat = false;
                    out << c;
                }
            } else {
                instruct += c;
            }
            continue;
        }
        
        if (c == '\\') {
            escaped = true;
        } else if (c == '%') {
            in_pat = true;
        } else {
            out << c;
        }
    }
    if (!instruct.empty()) {
        out << format_instruct(instruct, message, level);
    }
    return out.str();
}

void Logger::set_level(Level* level) {
    if (name == "root" && level == NO_LEVEL) {
        throw std::runtime_error("Root logger cannot have NO_LEVEL");
    }
    this->level = level;
}

Level* Logger::get_level() const {
    return level;
}

void Logger::set_pattern(const std::string &pattern) {
    this->pattern = pattern;
}

std::string Logger::get_pattern() const {
    return pattern;
}

void Logger::set_parent(Logger* parent) {
    this->parent = parent;
}

Logger* Logger::get_parent() const {
    return parent;
}

void Logger::log(const std::string &message, const Level* level) {
    if (propagate && parent != nullptr) {
        parent->log(message, level);
    }
    
    if (*level >= *get_effective_level()) {
        for (auto handler : handlers) {
            handler->log(log_format(message, level), level);
        }
    }
}

void Logger::trace(const std::string &message) {
    log(message, TRACE);
}

void Logger::debug(const std::string &message) {
    log(message, DEBUG);
}

void Logger::info(const std::string &message) {
    log(message, INFO);
}

void Logger::warn(const std::string &message) {
    log(message, WARN);
}

void Logger::error(const std::string &message) {
    log(message, ERROR);
}

void Logger::fatal(const std::string &message) {
    log(message, FATAL);
}

void Logger::add_handler(Handler *handler) {
    handlers.push_back(handler);
}

bool Logger::remove_handler(Handler *handler) {
    for (std::size_t i = 0; i < handlers.size(); ++i) {
        if (handlers[i] == handler) {
            handlers.erase(handlers.begin() + i);
            return true;
        }
    }
    return false;
}

void Logger::set_propagation(bool propagate) {
    this->propagate = propagate;
}

bool Logger::get_propagation() const {
    return propagate;
}

}
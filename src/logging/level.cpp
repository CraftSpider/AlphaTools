
#include "level.h"

namespace logging {

const Level Level::NO_LEVEL = Level();
const Level Level::TRACE = Level(0, "TRACE");
const Level Level::DEBUG = Level(10, "DEBUG");
const Level Level::INFO = Level(20, "INFO");
const Level Level::WARN = Level(30, "WARN");
const Level Level::ERROR = Level(40, "ERROR");
const Level Level::FATAL = Level(50, "FATAL");

Level::Level() noexcept {
    this->name = "NULL";
    this->priority = 0;
}

Level::Level(const int &priority, const std::string &name) noexcept {
    this->name = name;
    this->priority = priority;
}

std::string Level::get_name() {
    return name;
}

bool Level::operator==(const Level &level) const {
    return priority == level.priority && name == level.name;
}

bool Level::operator<=(const Level &level) const {
    return priority <= level.priority;
}

bool Level::operator>=(const Level &level) const {
    return priority >= level.priority;
}

Level::operator std::string() const {
    return name;
}

}
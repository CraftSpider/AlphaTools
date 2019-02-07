
#include "logging/level.h"

namespace logging {

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

bool Level::operator!=(const logging::Level &level) {
    return priority != level.priority || name != level.name;
}

bool Level::operator<=(const Level &level) const {
    return priority <= level.priority;
}

bool Level::operator>=(const Level &level) const {
    return priority >= level.priority;
}

bool Level::operator<(const logging::Level &level) const {
    return priority < level.priority;
}

bool Level::operator>(const logging::Level &level) const {
    return priority > level.priority;
}

Level::operator std::string() const {
    return name;
}

}
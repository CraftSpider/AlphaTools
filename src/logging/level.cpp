
#include "logging/level.h"

namespace logging {

Level::Level() noexcept {
    this->name = "NULL";
    this->priority = 0;
}

Level::Level(int priority, const std::string& name) noexcept {
    this->name = name;
    this->priority = priority;
}

std::string Level::get_name() {
    return name;
}

bool Level::operator==(const Level& level) const {
    return priority == level.priority && name == level.name;
}

bool Level::operator!=(const Level& level) {
    return priority != level.priority || name != level.name;
}

bool Level::operator<=(const Level& level) const {
    return priority <= level.priority;
}

bool Level::operator>=(const Level& level) const {
    return priority >= level.priority;
}

bool Level::operator<(const Level& level) const {
    return priority < level.priority;
}

bool Level::operator>(const Level& level) const {
    return priority > level.priority;
}

Level::operator std::string() const {
    return name;
}

Level* NO_LEVEL;
Level* TRACE;
Level* DEBUG;
Level* INFO;
Level* WARN;
Level* ERROR;
Level* FATAL;

void __ensure_levels() {
    if (NO_LEVEL != nullptr) {
        return;
    }
    NO_LEVEL = new Level();
    TRACE = new Level(0, "TRACE");
    DEBUG = new Level(10, "DEBUG");
    INFO = new Level(20, "INFO");
    ERROR = new Level(40, "ERROR");
    WARN = new Level(30, "WARN");
    FATAL = new Level(50, "FATAL");
}

}
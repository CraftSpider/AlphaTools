#pragma once

#include <string>

namespace logging {

/**
 * \brief Defines a logging detail level
 *
 * A level determines what messages a logger will or will not log. They have a name,
 * and are comparable. They can be converted to a string by name. By default, the logging
 * module provides levels from TRACE to FATAL. NO_LEVEL will print all logs.
 */
class Level {
    
    std::string name;
    int priority;

public:
    
    Level() noexcept;
    Level(const int& priority, const std::string& name) noexcept;
    
    std::string get_name();
    
    bool operator==(const Level& level) const;
    bool operator!=(const Level& level);
    bool operator<=(const Level& level) const;
    bool operator>=(const Level& level) const;
    bool operator>(const Level& level) const;
    bool operator<(const Level& level) const;
    
    explicit operator std::string() const;
    
};

extern Level* NO_LEVEL;
extern Level* TRACE;
extern Level* DEBUG;
extern Level* INFO;
extern Level* WARN;
extern Level* ERROR;
extern Level* FATAL;

void __ensure_levels();

}
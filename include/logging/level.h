#pragma once

#include <string>

namespace logging {

class Level {
    
    std::string name;
    int priority;

public:
    
    static const Level NO_LEVEL = Level();
    static const Level TRACE = Level(0, "TRACE");
    static const Level DEBUG = Level(10, "DEBUG");
    static const Level INFO = Level(20, "INFO");
    static const Level WARN = Level(30, "WARN");
    static const Level ERROR = Level(40, "ERROR");
    static const Level FATAL = Level(50, "FATAL");
    
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

}
#pragma once

#include <string>

/**
 * \file level.h
 * \brief Levels for logger and handler systems
 *
 * Contains the class defining levels for a logger. Can be used to define your own
 * levels with the Level constructor.
 */

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
    
    /**
     * \internal
     *
     * Construct a new 'invalid' Level, with no priority and a name indicating that
     * it was incorrectly initialized
     */
    Level() noexcept;
    /**
     * Construct a new level with the given name and priority.
     * \param priority Priority of the new Level
     * \param name Name of the new Level
     */
    Level(const int& priority, const std::string& name) noexcept;
    
    /**
     * Get the name of this level, as a string
     * \return Level name
     */
    std::string get_name();
    
    bool operator==(const Level& level) const;
    bool operator!=(const Level& level);
    bool operator<=(const Level& level) const;
    bool operator>=(const Level& level) const;
    bool operator>(const Level& level) const;
    bool operator<(const Level& level) const;
    
    /**
     * Levels can be cast to a string, if done so explicitly
     * \return Level as a string
     */
    explicit operator std::string() const;
    
};

extern Level* NO_LEVEL;
extern Level* TRACE;
extern Level* DEBUG;
extern Level* INFO;
extern Level* WARN;
extern Level* ERROR;
extern Level* FATAL;

/**
 * \internal
 *
 * Ensures that the default logging levels have been initialized correctly
 */
void __ensure_levels();

}
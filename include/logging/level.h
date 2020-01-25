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
    
    const char* name;
    int priority;
    
    /**
     * As levels are managed statically by the library, they can't be deleted by outside systems
     */
    ~Level() = default;

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
     *
     * \param priority Priority of the new Level
     * \param name Name of the new Level
     */
    Level(int priority, const char* name) noexcept;
    
    /**
     * Check if two levels are equal. Two levels are equal if their priority and name are both the same
     *
     * \param level Level to compare
     * \return Whether levels are the same
     */
    bool operator==(const Level& level) const;
    
    /**
     * Check if two levels are not equal. If either priority or name are different, they aren't equal
     *
     * \param level Level to compare
     * \return Whether levels are not the same
     */
    bool operator!=(const Level& level);
    
    /**
     * Check if this level is less than or equal to another level. This only considers the priority of the two
     * levels, name is not considered
     *
     * \param level Level to compare to
     * \return Whether level is less than or equal to this level
     */
    bool operator<=(const Level& level) const;
    
    /**
     * Check if this level is greater than or equal to another level. This only considers the priority of the two
     * levels, name is not considered
     *
     * \param level Level to compare to
     * \return Whether level is greater than or equal to this level
     */
    bool operator>=(const Level& level) const;
    
    /**
     * Check if this level is less than another level. This only considers the priority of the two
     * levels, name is not considered
     *
     * \param level Level to compare to
     * \return Whether level is less than this level
     */
    bool operator>(const Level& level) const;
    
    /**
     * Check if this level is greater than another level. This only considers the priority of the two
     * levels, name is not considered
     *
     * \param level Level to compare to
     * \return Whether level is greater than this level
     */
    bool operator<(const Level& level) const;
    
    /**
     * Levels can be cast to a string, if done so explicitly
     *
     * \return Level as a string
     */
    explicit operator std::string() const;
    
    /**
     * Get the name of this level, as a string
     *
     * \return Level name
     */
    std::string get_name();
    
    /**
     * Get the priority of this level, as an int
     *
     * \return level priority
     */
    int get_priority();
    
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
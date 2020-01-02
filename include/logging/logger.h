#pragma once

#include <string>
#include <vector>
#include "level.h"
#include "handler.h"

/**
 * \file logger.h
 * \brief Defines the logger class
 *
 * The base logger class. Can be subclassed for custom loggers, and is automatically constructed
 * by the logger factory functions. Attempts to be relatively generic, as much as is practical.
 */

/**
 * Default level that loggers are set to, on creation
 */
#define AT_DEFAULT_LOGGER_LEVEL (logging::INFO)

namespace logging {

/**
 * Built-in logger type, provides all the library functionality. May in the future be altered into a base type
 */
class Logger {

protected:
    
    bool propagate = true;
    Logger* parent = nullptr;
    std::string name;
    std::string pattern = "";
    Level* level;
    Level* stream_level;
    std::vector<Handler*> handlers;
    
    /**
     * Get the level of this logger, considering parents if this logger has no level
     *
     * \return Effective level of this logger
     */
    Level* get_effective_level() const;
    
    /**
     * Get the pattern of this logger, considering parents if this logger has no pattern
     *
     * \return Effective pattern of this logger
     */
    std::string get_effective_pattern() const;
    
    /**
     * Return the result of a format code for logging with a given instruction and context
     *
     * \param instruct Instruction to use
     * \param message Message to log
     * \param level Level logged at
     * \return Instruction result
     */
    std::string format_instruct(const std::string& instruct, std::string message, const Level* level);
    
    /**
     * Format a message for logging at a given level
     *
     * \param message Message to format
     * \param level Level logged at
     * \return Formatted message result
     */
    std::string log_format(const std::string& message, const Level* level);
    
    /**
     * As loggers are managed through the library, outside systems can't delete them
     */
    ~Logger() = default;

public:
    
    /**
     * Loggers cannot be created without a name
     */
    Logger() = delete;
    
    /**
     * Construct a logger with the default levels, no handlers, and the given name
     *
     * \param name Name of this logger
     */
    explicit Logger(const std::string& name);
    
    /**
     * Set the level of this logger through a stream operation
     *
     * \param level New logging level
     * \return Reference to this
     */
    Logger& operator<<(Level* level);
    
    /**
     * Log a string to the output of this logger through a stream operation
     *
     * \param input String to log
     * \return Reference to this
     */
    Logger& operator<<(const std::string& input);
    
    /**
     * Log a type that can be formatted with a stringstream through a stream operation.
     *
     * \tparam T Type being logged
     * \param input Instance of type
     * \return Reference to this
     */
    template<typename T>
    Logger& operator<<(const T input);
    
    /**
     * Set the level of this logger, any attempt to log below this level will be ignored
     *
     * \param level New logging level
     */
    void set_level(Level* level);
    
    /**
     * Get the current level of this logger
     *
     * \return Current logging level
     */
    Level* get_level() const;
    
    /**
     * Set the pattern for this logger. This pattern will be used to format the output of logging operations.
     * Valid specifiers include %l for level, %m for message, and %n for name
     *
     * \param pattern New pattern to use
     */
    void set_pattern(const std::string& pattern);
    
    /**
     * Get the pattern for this logger. This is the pattern used to format output
     *
     * \return Current logging pattern
     */
    std::string get_pattern() const;
    
    /**
     * Set what logger is the parent of this logger. Loggers without a level inherit it from their parent, and if
     * set logs are propagated and handled by the parent as well as this logger. If a logger has no parent, it is
     * parented to the root logger.
     *
     * \param parent New parent logger
     */
    void set_parent(Logger* parent);
    
    /**
     * Get the current parent of this logger
     *
     * \return Current parent logger, or nullptr if this is the root logger.
     */
    Logger* get_parent() const;
    
    /**
     * Set whether this logger propagates logs to its parent
     *
     * \param propagate New propagation setting
     */
    void set_propagation(bool propagate);
    
    /**
     * Whether the logger is propagating new logs to its parent
     *
     * \return Current propagation setting
     */
    bool get_propagation() const;
    
    /**
     * Log a message at a given level
     *
     * \param message Message to log
     * \param level Level to log at
     */
    void log(const std::string& message, const Level* level);
    
    /**
     * Log a message with the TRACE level
     *
     * \param message Message to log
     */
    void trace(const std::string& message);
    
    /**
     * Log a message with the DEBUG level
     *
     * \param message Message to log
     */
    void debug(const std::string& message);
    
    /**
     * Log a message with the INFO level
     *
     * \param message Message to log
     */
    void info(const std::string& message);
    
    /**
     * Log a message with the WARN level
     *
     * \param message Message to log
     */
    void warn(const std::string& message);
    
    /**
     * Log a message with the ERROR level
     *
     * \param message Message to log
     */
    void error(const std::string& message);
    
    /**
     * Log a message with the FATAL level
     *
     * \param message Message to log
     */
    void fatal(const std::string& message);
    
    /**
     * Add a new handler. Handlers are the devices which are actually logged to, representing the console, a file, or
     * any other location for logs to be sent to
     *
     * \param handler Handler to add
     */
    void add_handler(Handler* handler);
    
    /**
     * Remove a previously registered handler from this logger
     *
     * \param handler Handler to remove
     * \return Whether the handler was successfully moved
     */
    bool remove_handler(Handler* handler);
    
};

}

#include "logger.tpp"

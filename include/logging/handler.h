#pragma once

#include <string>
#include "level.h"

/**
 * \file handler.h
 * \brief Handlers for logging output
 *
 * Contains the abstract class and several default implementations of the Handler protocol for loggers.
 * A logger can have multiple handlers, each responsible for one form of output and each can have its own minimum
 * logging level it outputs at.
 */

/**
 * Default level that handlers are set to, on creation
 */
#define AT_DEFAULT_HANDLER_LEVEL (logging::TRACE)

namespace logging {

/**
 * Defines a logging handler, which is responsible for outputting the results of a log operation.
 * This class is abstract, and child classes are expected to implement the actual handling of log operations.
 */
class Handler {
protected:
    
    Level* level;

public:
    
    /**
     * Default constructor to construct a new Handler
     */
    Handler();
    
    /**
     * Set the current logging level of this handler. Logs below this level won't be output
     *
     * \param level New level to log at
     */
    void set_level(Level* level);
    
    /**
     * Actually log a message to output
     *
     * \param message Message to log. May contain newlines or other unusual characters
     * \param level Level being logged at
     * \return void
     */
    virtual void log(const std::string& message, const Level* level) = 0;
    
};

/**
 * A handler that outputs log messages to stdout. Will automatically get a reference to stdout from
 * std::cout
 */
class ConsoleHandler : public Handler {
public:
    
    void log(const std::string& message, const Level* level) override;
    
};

/**
 * A handler that outputs log messages to stderr. Will automatically get a reference to stderr from
 * std::cerr
 */
class ErrorHandler : public Handler {
public:
    
    ErrorHandler();
    
    void log(const std::string& message, const Level* level) override;
    
};

/**
 * A handler that outputs log messages to a file. The filename can be specified either as relative or
 * absolute, and a reference to it will be held open for the life of this handler. Output is not flushed
 * until the handler is destructed.
 */
class FileHandler : public Handler {
    
    std::ofstream* fileout;

public:
    
    /**
     * Construct a new FileHandler that appends to a given file
     *
     * \param filename File to log to
     */
    explicit FileHandler(const std::string& filename);
    
    /**
     * Deconstruct a FileHandler, releasing hold of the file
     */
    ~FileHandler();
    
    void log(const std::string& message, const Level* level) override;
    
};

}
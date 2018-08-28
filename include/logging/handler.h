#pragma once

#include <string>
#include "level.h"

#define DEFAULT_HANDLER_LEVEL (logging::Level::TRACE)

namespace logging {

class Handler {

protected:
    
    std::string pattern = "";
    Level level;

public:
    
    Handler();
    
    void set_level(const Level& level);
    
    void set_pattern(const std::string& pattern);
    
    // TODO: pattern handling
    virtual void log(const std::string& message, const Level& level) = 0;
    
};

class ConsoleHandler : public Handler {

public:
    
    void log(const std::string& message, const Level& level) override;
    
};

class ErrorHandler : public Handler {

public:

    ErrorHandler();

    void log(const std::string& message, const Level& level) override;

};

class FileHandler : public Handler {

    std::ofstream* fileout;

public:

    explicit FileHandler(const std::string& filename);
    ~FileHandler();

    void log(const std::string& message, const Level& level) override;

};

}
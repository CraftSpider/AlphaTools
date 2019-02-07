#include <iostream>
#include <map>
#include "logging/logging.h"

namespace logging {

static std::map<std::string, Logger*> loggers = std::map<std::string, Logger*>();

void set_default_level(const Level& level) {
    get_root_logger()->set_level(level);
}

void add_default_handler(Handler* handler) {
    get_root_logger()->add_handler(handler);
}

bool remove_default_handler(Handler* handler) {
    return get_root_logger()->remove_handler(handler);
}

Logger* get_root_logger() {
    if (loggers.count("root")) {
        return loggers["root"];
    }
    Logger *log = new Logger("root");
    loggers.emplace("root", log);
    log->set_level(DEFAULT_LOGGER_LEVEL);
    log->set_pattern("%l: %m");
    
    ConsoleHandler *ch = new ConsoleHandler();
    ErrorHandler *eh = new ErrorHandler();
    log->add_handler(ch);
    log->add_handler(eh);
    
    return log;
}

Logger* get_logger(std::string name, bool auto_parent) {
    if (loggers.count(name)) {
        return loggers[name];
    }
    Logger *log = new Logger(name);
    // TODO: automatically set tree from . separated names
    log->set_parent(get_root_logger());
    loggers.emplace(name, log);
    return log;
}

}

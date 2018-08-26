#include <iostream>
#include <map>
#include "logging.h"

namespace logging {

static std::map<std::string, Logger*> loggers = std::map<std::string, Logger*>();
static ConsoleHandler *ch = new ConsoleHandler();

void set_default_level(const Level& level) {
    get_root_logger()->set_level(level);
}

Logger* get_root_logger() {
    if (loggers.count("root")) {
        return loggers["root"];
    }
    Logger *log = new Logger("root");
    log->set_level(DEFAULT_LOGGER_LEVEL);
    loggers.emplace("root", log);
    log->add_handler(ch);
    return log;
}

Logger* get_logger(const std::string& name) {
    if (loggers.count(name)) {
        return loggers[name];
    }
    Logger *log = new Logger(name);
    log->set_parent(get_root_logger());
    loggers.emplace(name, log);
    log->add_handler(ch);
    return log;
}

}

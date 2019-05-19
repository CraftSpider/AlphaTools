#include <iostream>
#include <map>
#include "logging/logging.h"

namespace logging {

static std::map<std::string, Logger*>* loggers;

void __ensure_loggers() {
    __ensure_levels();
    if (loggers == nullptr) {
        loggers = new std::map<std::string, Logger *>();
    }
}

void set_default_level(Level* level) {
    get_root_logger()->set_level(level);
}

void add_default_handler(Handler* handler) {
    get_root_logger()->add_handler(handler);
}

bool remove_default_handler(Handler* handler) {
    return get_root_logger()->remove_handler(handler);
}

Logger* get_root_logger() {
    __ensure_loggers();
    if (loggers->count("root")) {
        return loggers->at("root");
    }
    Logger *log = new Logger("root");
    loggers->emplace("root", log);
    
    log->set_level(DEFAULT_LOGGER_LEVEL);
    log->set_pattern("%l: %m");
    
    ConsoleHandler *ch = new ConsoleHandler();
    ErrorHandler *eh = new ErrorHandler();
    log->add_handler(ch);
    log->add_handler(eh);
    
    return log;
}

Logger* get_logger(const std::string& name, bool auto_parent) {
    __ensure_loggers();
    if (loggers->count(name)) {
        return loggers->at(name);
    }
    Logger *log = new Logger(name);
    loggers->emplace(name, log);
    
    if (auto_parent) {
        std::string parent_name = "root";
        int pos = name.find_last_of(".");
        if (pos >= 0)
            parent_name = name.substr(0, pos);
        Logger *parent = get_logger(parent_name, true);
        log->set_parent(parent);
    } else {
        log->set_parent(get_root_logger());
    }
    return log;
}

}

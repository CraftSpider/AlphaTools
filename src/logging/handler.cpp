
#include <iostream>
#include "handler.h"

namespace logging {

Handler::Handler() {
    this->level = Level::TRACE;
}

void Handler::set_level(const Level &level) {
    this->level = level;
}

void ConsoleHandler::log(const std::string &message, const Level &level) {
    if (level >= this->level) {
        std::cout << (std::string)level << ": " << message << std::endl;
    }
}

}
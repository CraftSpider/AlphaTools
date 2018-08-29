
#include <iostream>
#include <fstream>
#include "logging/handler.h"

namespace logging {

Handler::Handler() {
    this->level = DEFAULT_HANDLER_LEVEL;
}

void Handler::set_level(const Level &level) {
    this->level = level;
}

void ConsoleHandler::log(const std::string &message, const Level &level) {
    if (level >= this->level) {
        std::cout << message << std::endl;
    }
}

ErrorHandler::ErrorHandler() {
    this->level = Level::ERROR;
}

void ErrorHandler::log(const std::string &message, const logging::Level &level) {
    if (level >= this->level) {
        std::cerr << message << std::endl;
    }
}

FileHandler::FileHandler(const std::string &filename) {
    fileout = new std::ofstream(filename);
}

FileHandler::~FileHandler() {
    delete fileout;
}

void FileHandler::log(const std::string &message, const logging::Level &level) {
    if (level >= this->level) {
        *fileout << message << '\n';
    }
}

}
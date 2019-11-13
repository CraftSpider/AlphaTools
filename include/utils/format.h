#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <system_error>

namespace util {

class format_error : public std::runtime_error {
public:
    explicit format_error(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename T>
std::string spec_handler(std::string spec, T* arg);

template<typename... Args>
std::string format(std::string format, Args... args);

}

#include "format.tpp"

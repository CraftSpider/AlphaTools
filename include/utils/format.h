#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

/**
 * \file format.h
 * \brief Generic type-safe format function
 */

namespace util {

class format_error : public std::runtime_error {
public:
    explicit format_error(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename T>
std::string spec_handler(std::string spec, T* arg);

// Specializations provided
template<>
std::string spec_handler<std::string>(std::string spec, std::string* arg);
template<>
std::string spec_handler<int>(std::string spec, int* arg);
template<>
std::string spec_handler<const char*>(std::string spec, const char** arg);
template<>
std::string spec_handler<uchar*>(std::string spec, uchar** arg);

template<typename... Args>
std::string format(std::string format, Args... args);

}

#include "format.tpp"

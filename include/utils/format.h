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

/**
 * Error thrown if the formatter encounters an invalid format string
 */
class format_error : public std::runtime_error {
public:
    
    /**
     * Create a new format_error from a given error message
     *
     * \param msg Message for the error
     */
    explicit format_error(const std::string& msg) : std::runtime_error(msg) {}
    
};

/**
 * Handler for a type in the formatter. Accepts any type with the `__format__` function defined, or any type with a
 * specialized handler defined (see below)
 *
 * \tparam T Type to format
 * \param spec Format specifier
 * \param arg Instance of T
 * \return Formatted value
 */
template<typename T>
std::string spec_handler(std::string spec, T* arg);

// Specializations provided

/**
 * Spec handler for the standard library string type
 *
 * \param spec Format specifier
 * \param arg Instance of `std::string`
 * \return Formatted string
 */
template<>
std::string spec_handler<std::string>(std::string spec, std::string* arg);

/**
 * Spec handler for the builtin int type
 *
 * \param spec Format specifier
 * \param arg Instance of `int`
 * \return Formatted int
 */
template<>
std::string spec_handler<int>(std::string spec, int* arg);

/**
 * Spec handler for the builtin const char* type, interprets it as a string
 *
 * \param spec Format specifier
 * \param arg Instance of `const char*`
 * \return Formatter const char array
 */
template<>
std::string spec_handler<const char*>(std::string spec, const char** arg);

/**
 * Spec handler for the builtin `unsigned char*` type, interprets it as a byte array
 * \param spec Format specifier
 * \param arg Instance of `uchar*`
 * \return Formatted uchar array
 */
template<>
std::string spec_handler<uchar*>(std::string spec, uchar** arg);

/**
 * Format a string in a type-safe manner. Can be errored with specially crafted input, but is more difficult to do
 * with this than the builtin formatting utilities.
 *
 * Syntax:
 * `{type:specifier}`
 * Commonly, type is auto-detected, and specifier is per-type
 *
 * \tparam Args Variadic pack of argument types
 * \param format Format string to use
 * \param args Pack of arguments to format
 * \return New formatted string
 */
template<typename... Args>
std::string format(std::string format, Args... args);

}

#include "format.tpp"

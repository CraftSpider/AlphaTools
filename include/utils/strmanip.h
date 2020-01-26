#pragma once

#include <string>
#include "types.h"

/**
 * \file strmanip.h
 * \brief String manipulation utilities
 */

namespace util {

/**
 * Get the reverse of the input string, without affecting the input
 *
 * \param str String to reverse
 * \return Reversed string
 */
std::string reverse(const std::string& str);

/**
 * Check whether an input string starts with a given string of characters
 *
 * \param val String to check
 * \param start What the string is expected to start with
 * \return Whether val starts with the given value
 */
bool starts_with(const std::string& val, const std::string& start);

/**
 * Check whether an input string ends with a given string of characters
 *
 * \param val String to check
 * \param end What the string is expected to end with
 * \return Whether val ends with the given value
 */
bool ends_with(const std::string& val, const std::string& end);

/**
 * Get the uppercase form of the input string, without affecting the input
 *
 * \param str String to uppercase
 * \return Uppercased string
 */
std::string to_uppercase(const std::string& str);

/**
 * Get the lowercase form of the input string, without affecting the input
 *
 * \param str String to lowercase
 * \return Lowercased strings
 */
std::string to_lowercase(const std::string& str);

/**
 * Convert a byte array to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Byte array to read
 * \param length Length of the array
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string btoh(const uchar* val, const ulong length, const bool prefix = true, const bool pad = false);

/**
 * Convert a byte array to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Byte array to read
 * \param length Length of the array
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string btoh(const char* val, const ulong length, const bool prefix = true, const bool pad = false);

/**
 * Convert a ulong to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Ulong to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string ltoh(const ulong val, bool prefix = true, bool pad = false);

/**
 * Convert a long to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Long to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string ltoh(const slong val, bool prefix = true, bool pad = false);

/**
 * Convert a uint to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Uint to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string itoh(const uint val, bool prefix = true, bool pad = false);

/**
 * Convert an int to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Int to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string itoh(const int val, bool prefix = true, bool pad = false);

/**
 * Convert a ushort to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Ushort to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string stoh(const ushort val, bool prefix = true, bool pad = false);

/**
 * Convert a short to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Short to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string stoh(const short val, bool prefix = true, bool pad = false);

/**
 * Convert a uchar to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Uchar to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string ctoh(const uchar val, bool prefix = true, bool pad = false);

/**
 * Convert a char to a hex string representing its value
 *
 * \tparam E What Endianness to use
 * \param val Char to read
 * \param prefix Whether to prefix the result with `"0x"`
 * \param pad Whether to pad the start of the result so it will always be an even number of characters
 * \return Input formatted as a hex string
 */
template<Endian E = Endian::BIG>
std::string ctoh(const char val, bool prefix = true, bool pad = false);

}

#include "strmanip.tpp"

#pragma once

#include <fstream>
#include "types.h"

/**
 * \file io.h
 * \brief File IO utilities
 */

namespace util {

/**
 * Read an unsigned long from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a ulong
 */
template<Endian E = Endian::BIG>
ulong next_ulong(std::istream& file, const ulong length = 8);

/**
 * Read an unsigned int from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a uint
 */
template<Endian E = Endian::BIG>
uint next_uint(std::istream& file, const ulong length = 4);

/**
 * Read an unsigned short from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a ushort
 */
template<Endian E = Endian::BIG>
ushort next_ushort(std::istream& file, const ulong length = 2);

/**
 * Read an unsigned char from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a uchar
 */
template<Endian E = Endian::BIG>
uchar next_uchar(std::istream& file, const ulong length = 1);

/**
 * Read a signed long from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a long
 */
template<Endian E = Endian::BIG>
slong next_long(std::istream& file, const ulong length = 8);

/**
 * Read a signed int from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as an int
 */
template<Endian E = Endian::BIG>
sint next_int(std::istream& file, const ulong length = 4);

/**
 * Read a signed short from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a short
 */
template<Endian E = Endian::BIG>
sshort next_short(std::istream& file, const ulong length = 2);

/**
 * Read a signed char from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a char
 */
template<Endian E = Endian::BIG>
schar next_char(std::istream& file, const ulong length = 1);

/**
 * Read a float from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a float
 */
template<Endian E = Endian::BIG>
float next_float(std::istream& file, const ulong length = 4);

/**
 * Read a double from a byte input stream, with optional number of bytes to read
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read
 * \return Next value in the file as a double
 */
template<Endian E = Endian::BIG>
double next_double(std::istream& file, const ulong length = 8);

/**
 * Read an ASCII string from a byte input stream, with optional number of bytes to read. The default of 0
 * assumes that the string is null terminated, and reads till the next null-terminator
 *
 * \tparam E What Endianness to use
 * \param file Stream to read from
 * \param length Number of bytes to read, or 0 for auto-detected length
 * \return The next whole string from the file
 */
template<Endian E = Endian::BIG>
std::string next_string(std::istream& file, const ulong length = 0);

/**
 * Write an unsigned long to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_ulong(std::ostream& file, const ulong out, const ulong length = 8);

/**
 * Write an unsigned int to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_uint(std::ostream& file, const uint out, const ulong length = 4);

/**
 * Write an unsigned short to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_ushort(std::ostream& file, const ushort out, const ulong length = 2);

/**
 * Write an unsigned char to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_uchar(std::ostream& file, const uchar out, const ulong length = 1);

/**
 * Write a signed long to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_long(std::ostream& file, const slong out, const ulong length = 8);

/**
 * Write a signed int to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_int(std::ostream& file, const sint out, const ulong length = 4);

/**
 * Write a signed short to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_short(std::ostream& file, const sshort out, const ulong length = 2);

/**
 * Write a signed char to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_char(std::ostream& file, const schar out, const ulong length = 1);

/**
 * Write a float to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_float(std::ostream& file, float out, const ulong length = 4);

/**
 * Write a double to a byte output stream, with optional number of bytes to write
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write
 */
template<Endian E = Endian::BIG>
void write_double(std::ostream& file, double out, const ulong length = 8);

/**
 * Write a string to a byte output stream, with optional number of bytes to write. The default of 0
 * will use the string size() function to determine the length of the string.
 *
 * \tparam E What Endianness to use
 * \param file Stream to write to
 * \param out Value to write to file
 * \param length Number of bytes to write, or 0 to for auto-detected length.
 */
template<Endian E = Endian::BIG>
void write_string(std::ostream& file, const std::string& out, const ulong length = 0);

}

#include "io.tpp"

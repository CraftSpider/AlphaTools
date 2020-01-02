#pragma once

#include <cstdint>

/**
 * \file types.h
 * \brief Defines AlphaTools global type shorthands
 *
 * \author CraftSpider
 */

/**
 * Unsigned 1 byte integer
 */
typedef std::uint8_t uchar;

/**
 * Unsigned 2 byte integer
 */
typedef std::uint16_t ushort;

/**
 * Unsigned 4 byte integer
 */
typedef std::uint32_t uint;

/**
 * Unsigned 8 byte integer
 */
typedef std::uint64_t ulong;

/**
 * Signed 1 byte integer
 */
typedef std::int8_t schar;

/**
 * Signed 2 byte integer
 */
typedef std::int16_t sshort;

/**
 * Signed 4 byte integer
 */
typedef std::int32_t sint;

/**
 * Signed 8 byte integer
 */
typedef std::int64_t slong;

/**
 * Types of endianness a computer might have
 */
enum Endian {
    BIG, LITTLE
};

// TODO: Move whole project into a namespace

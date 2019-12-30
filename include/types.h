#pragma once

#include <cstdint>

/**
 * \file types.h
 * \brief Defines AlphaTools global type shorthands
 *
 * \author CraftSpider
 */

typedef std::uint8_t uchar;
typedef std::uint16_t ushort;
typedef std::uint32_t uint;
typedef std::uint64_t ulong;

typedef std::int8_t schar;
typedef std::int16_t sshort;
typedef std::int32_t sint;
typedef std::int64_t slong;

enum Endian {
    BIG, LITTLE
};

// TODO: Move whole project into a namespace

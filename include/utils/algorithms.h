#pragma once

#include "types.h"

/**
 * \file algorithms.h
 * \brief Common generic algorithms
 */

namespace util {

/**
 * Generate a crc32 hash of a given character array
 * \param input Array pointer
 * \param length Length of the array
 * \return crc32 hash as an unsigned integer
 */
uint crc32(const uchar* input, const ulong length);

}

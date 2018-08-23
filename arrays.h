#pragma once

#include "utils.h"

namespace util {

/**
 * Reverse an array in place. Returns the pointer to the array, to allow chaining.
 * @tparam T
 * @param arr
 * @param len
 * @return
 */
template<typename T>
T *reverse(T *arr, ulong len);

/**
 * Convert an array from one endian into another, reversing every X items.
 * size == len makes this equivalent to reverse.
 * @tparam T
 * @param arr
 * @param len
 * @param size
 * @return
 */
template<typename T>
T *endian_convert(T *arr, ulong len, ulong size = 4);

}

#include "arrays.tpp"

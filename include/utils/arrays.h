#pragma once

#include "types.h"

/**
 * \file arrays.h
 * \brief Array utilities
 *
 * Defines various utilities for manipulation and comparison of C arrays, higher level than default
 * but still lower level than a vector or linked list
 */

namespace util {

/**
 * Check 2 arrays for equality, defined as all items being equal
 * \tparam T The type of the arrays
 * \param first First array to check
 * \param second Second array to check
 * \param length Length of both arrays
 * \return Whether the arrays are equivalent
 */
template<typename T>
bool compare(T* first, T* second, const ulong length);

/**
 * Check 2 2D arrays for equality, defined as all items being equal
 * \tparam T The type of the 2D arrays
 * \param first First array to check
 * \param second Second array to check
 * \param height Number of items in the first array
 * \param width Number of items in the second arrays
 * \return Whether the arrays are equivalent
 */
template<typename T>
bool compare_2D(T** first, T** second, const ulong height, const ulong width);

/**
 * Check 2 square 2D arrays for equality, defined as all items being equal
 * \tparam T The type of the 2D arrays
 * \param first First array to check
 * \param second Second array to check
 * \param size Number of items in the NxN arrays
 * \return Whether the arrays are equivalent
 */
template<typename T>
bool compare_2D(T** first, T** second, const ulong size);

/**
 * Copy values from a source array into a destination array
 * \tparam T The type of the arrays
 * \param source The array to copy from
 * \param dest The array to copy to
 * \param length The length of the array to copy
 */
template<typename T>
void copy(const T* source, T* dest, const ulong length);

/**
 * Copy values from a 2D source array to a 2D destination array
 * \tparam T The type of the 2D arrays
 * \param source The array to copy from
 * \param dest The array to copy to
 * \param height The number of items in the first source array
 * \param width The number of items in the second source arrays
 */
template<typename T>
void copy_2D(T** source, T** dest, const ulong height, const ulong width);

/**
 * Copy values from a 2D source array to a 2D destination array
 * \tparam T The type of the 2D arrays
 * \param source The array to copy from
 * \param dest The array to copy to
 * \param size Number of items in the NxN source array
 */
template<typename T>
void copy_2D(T** source, T** dest, const ulong size);

/**
 * Reverse an array in place. Returns the pointer to the array, to allow chaining.
 * \tparam T The type of the array
 * \param arr Array pointer
 * \param len Length of the array
 * \return Array pointer, allows chaining
 */
template<typename T>
T* reverse(T* arr, const ulong len);

/**
 * Convert an array from one endian into another, reversing every X items.
 * size == len makes this equivalent to reverse.
 * \tparam T The type of the array
 * \param arr Array pointer
 * \param len Length of the array
 * \param size How many bytes per endian block, default to 4
 * \return Array pointer, allows chaining
 */
template<typename T>
T* endian_convert(T* arr, const ulong len, const ulong size = 4);

}

#include "arrays.tpp"

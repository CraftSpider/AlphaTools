#pragma once

#include "types.h"

/**
 * \file memory.h
 * \brief Raw memory access
 */

namespace util {

/**
 * Copy a type, irrespective of whether the type has a public copy constructor
 * This can be very dangerous, most things without copy constructors are like that intentionally
 *
 * \tparam T Type to copy
 * \param obj Reference to an instance of the type
 * \return New instance of the type
 */
template<typename T>
T* raw_copy(T& obj);

/**
 * Move a type into a new instance, irrespective of whether the type has a public move constructor
 * This can be very dangerous, most things without move constructors are like that intentionally
 * Zeros the source as it goes, so that any deletes are on `nullptr`.
 *
 * \tparam T Type to move
 * \param src Reference to an instance of the tye
 * \return New instance of the type
 */
template<typename T>
T* raw_move(T& src);

/**
 * Move a type over an existing other instance, irrespective of whether the type has a public move assignment operator
 * This can be very dangerous, most things without move operators are like that intentionally
 *
 * \tparam T Type to move
 * \param src Reference to an instance of the type to move
 * \param dst Reference to an instance of the type to move over
 * \return A reference to the destination type
 */
template<typename T>
T& raw_move(T& src, T& dst);

}

#include "memory.tpp"

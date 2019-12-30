#pragma once

#include "types.h"

/**
 * \file memory.h
 * \brief Raw memory access
 */

namespace util {

template<typename T>
T* raw_copy(T& obj);

template<typename T>
T* raw_move(T& src);

template<typename T>
T& raw_move(T& src, T& dst);

}

#include "memory.tpp"

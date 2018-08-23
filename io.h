#pragma once

#include <fstream>
#include "types.h"

namespace util {

template <Endian e = BIG>
ulong next_ulong(std::istream &file, const ulong length = 8);

template <Endian e = BIG>
uint next_uint(std::istream &file, const ulong length = 4);

template <Endian e = BIG>
ushort next_ushort(std::istream &file, const ulong length = 2);

template <Endian e = BIG>
uchar next_uchar(std::istream &file, const ulong length = 2);

}

#include "io.tpp"

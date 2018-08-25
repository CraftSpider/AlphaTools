#pragma once

#include <string>
#include "types.h"

namespace util {

std::string reverse(const std::string& str);

bool starts_with(const std::string &val, const std::string &start);

bool ends_with(const std::string &val, const std::string &end);

template <Endian E = BIG>
std::string ltoh(const ulong val);

template <Endian E = BIG>
std::string ltoh(const long val);

std::string char_format(const std::string& format, const uchar *data);

}

#include "strings.tpp"

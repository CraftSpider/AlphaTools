#pragma once

#include <string>

#if defined(_WIN32) && !defined(__CYGWIN__)
#define WINCOMPAT 1
#elif defined(_WIN32) || defined(__CYGWIN__)
#define WINCOMPAT 2
#elif defined(__linux__)
#define LINUXCOMPAT 1
#else
#warning Unrecognized system, generic defaults may be unreliable
#endif

std::string get_username();

std::string get_computer_name();

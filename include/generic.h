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

std::string demangle(std::string name);

class SysInfo {
public:
    
    class Endianness {
    private:
        
        static constexpr std::uint32_t __magic = 0x01020304;
        static constexpr std::uint8_t __char = (const std::uint8_t&)__magic;
        
    public:
        
        static constexpr bool little = __char == 0x04;
        static constexpr bool big = __char == 0x01;
        static_assert(little || big, "Cannot determine endianness");
    
        Endianness() = delete;
    };
    
    SysInfo() = delete;
};

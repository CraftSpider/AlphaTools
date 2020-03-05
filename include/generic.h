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

/**
 * \file generic.h
 * \brief Generic ways to do platform or OS specific things
 */

/**
 * Get the username of the current user, if it can be determined. If not, returns the empty string
 *
 * \return Username of the current user
 */
std::string get_username();

/**
 * Get the name of the current system, if it can be determined. If not, returns the empty string
 *
 * \return System name
 */
std::string get_computer_name();

/**
 * Demangle a name based on the compiler used to create this binary, if the compiler supports such a feature.
 * Returns the name unchanged if it can't determine what method to use, throws an error if the demangler method errors
 *
 * \param name Symbol name to demangle
 * \return Demangled name or unchanged
 */
std::string demangle(const std::string& name);

/**
 * System-specific information, determined at compile time. A class instead of a namespace to avoid
 * possible static initialization issues. Cannot be construced, doesn't have any non-static members.
 */
namespace SysInfo {
    
    /**
     * Info about the endianness of the current system
     *
     * \TODO: Check whether current solution is UB
     */
    class Endianness {
    private:
        
        static constexpr std::uint32_t __magic = 0x01020304;
        static constexpr std::uint8_t __char = (const std::uint8_t&)__magic;
        
    public:
        
        /**
         * Whether the system uses little-endian
         */
        static constexpr bool little = __char == 0x04;
        
        /**
         * Whether the system uses big-endian
         */
        static constexpr bool big = __char == 0x01;
        static_assert(little || big, "Cannot determine endianness");
    
        Endianness() = delete;
    };
    
}

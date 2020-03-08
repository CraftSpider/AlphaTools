
#include "at_tests"
#include "test_generic.h"
#include "generic.h"

#include <iostream>
#include <typeinfo>

class MangleTest {
    MangleTest() = default;
};


void test_username() {
    ASSERT(get_username() != "USER");
}

void test_hostname() {
    ASSERT(get_hostname() != "HOSTNAME");
}

void test_demangle() {
#ifdef LINUXCOMPAT
    std::string name = typeid(MangleTest).name();
    ASSERT(demangle(name) == "MangleTest");
#elif defined(WINCOMPAT)
    std::string name = typeid(MangleTest).raw_name();
    name.erase(0, 1);
    ASSERT(demangle(name) == "class MangleTest");
#endif
}

void test_endianness() {
    ASSERT(SysInfo::Endianness::little != SysInfo::Endianness::big);
}

void run_generic_tests() {
    TEST(test_username)
    TEST(test_hostname)
    TEST(test_demangle)
    TEST(test_endianness)
}

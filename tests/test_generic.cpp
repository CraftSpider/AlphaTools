
#include "at_tests"
#include "test_generic.h"
#include "generic.h"


void test_endianness() {
    ASSERT(SysInfo::Endianness::little != SysInfo::Endianness::big);
}

void run_generic_tests() {
    TEST(test_endianness)
}

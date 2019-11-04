
#include "at_tests"
#include "test_generic.h"
#include "generic.h"


void test_endianness() {
    testing::assert(SysInfo::Endianness::little != SysInfo::Endianness::big);
}

void run_generic_tests() {
    TEST(test_endianness)
}

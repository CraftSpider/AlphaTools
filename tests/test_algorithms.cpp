
#include "at_tests"
#include "test_algorithms.h"
#include "utils/algorithms.h"

void test_crc32() {
    uchar data1[1] = {0};
    uchar data2[4] = {1, 2, 3, 4};
    
    ASSERT(util::crc32(data1, 1) == 0xD202EF8D);
    ASSERT(util::crc32(data2, 4) == 0xB63CFBCD);
}

void run_algorithms_tests() {
    TEST(test_crc32)
}

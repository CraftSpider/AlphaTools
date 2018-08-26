
#include "test_bytes.h"
#include "../include/tests/test.h"
#include "../include/utils/bytes.h"
#include "../include/utils/arrays.h"

using namespace util;

void test_btol() {
    uchar test1[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test1) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test1) == 0x0102030405060708);
    char test2[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test2) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test2) == 0x0102030405060708);
}

void test_ltob() {
    ulong test1 = 0xFFFEFDFCFBFAF9F8;
    uchar expected1[8] = {255, 254, 253, 252, 251, 250, 249, 248};
    ASSERT(compare(ltob<BIG>(test1, 8), expected1, 8));
    ASSERT(compare(ltob<LITTLE>(test1, 8), reverse(expected1, 8), 8));
    
    ulong test2 = 0x0;
    const uchar expected2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    long test3 = 0xFFFEFDFCFBFAF9F8;
    
    
    long test4 = 0x0;
}

void run_bytes_tests() {
    TEST(test_btol)
    TEST(test_ltob)
}
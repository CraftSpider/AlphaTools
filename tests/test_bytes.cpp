
#include "test_bytes.h"
#include "tests/test.h"
#include "utils/bytes.h"
#include "utils/arrays.h"

using namespace util;

// Don't need to test the range explicitly, as they're implicitly included by the
// non-ranged versions. If this is no longer true, they'll need to be added.

void test_btol() {
    uchar test1[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test1) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test1) == 0x0102030405060708);
    
    char test2[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test2) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test2) == 0x0102030405060708);
}

void test_btoi() {
    // TODO
    throw testing::skip_test();
}

void test_btos() {
    // TODO
    throw testing::skip_test();
}

void test_btoc() {
    // TODO
    throw testing::skip_test();
}

void test_ltob() {
    ulong test1 = 0xFFFEFDFCFBFAF9F8;
    uchar expected1[8] = {255, 254, 253, 252, 251, 250, 249, 248};
    ASSERT(compare(ltob<BIG>(test1, 8), expected1, 8));
    ASSERT(compare(ltob<LITTLE>(test1, 8), reverse(expected1, 8), 8));
    
    ulong test2 = 0x0;
    uchar expected2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    ASSERT(compare(ltob<BIG>(test2, 8), expected2, 8));
    ASSERT(compare(ltob<LITTLE>(test2, 8), reverse(expected2, 8), 8));
    
    long test3 = 0xFFFEFDFCFBFAF9F8;
    char expected3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    ASSERT(compare(ltob<BIG>(test3, 8), expected3, 8));
    ASSERT(compare(ltob<LITTLE>(test3, 8), reverse(expected3, 8), 8));
    
    long test4 = 0x0;
    char expected4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    ASSERT(compare(ltob<BIG>(test4, 8), expected4, 8));
    ASSERT(compare(ltob<LITTLE>(test4, 8), reverse(expected4, 8), 8));
}

void test_itob() {
    // TODO
    throw testing::skip_test();
}

void test_stob() {
    // TODO
    throw testing::skip_test();
}

void test_ctob() {
    // TODO
    throw testing::skip_test();
}

void run_bytes_tests() {
    TEST(test_btol)
    TEST(test_btoi)
    TEST(test_btos)
    TEST(test_btoc)
    
    TEST(test_ltob)
    TEST(test_itob)
    TEST(test_stob)
    TEST(test_ctob)
}
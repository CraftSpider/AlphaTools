
#include "at_tests"
#include "test_bytes.h"
#include "utils/bytes.h"
#include "utils/arrays.h"

using namespace util;

void test_get_bit() {
    uchar test1[] = {0xAA};
    
    ASSERT(get_bit(test1, 0));
    ASSERT(!get_bit(test1, 1));
    ASSERT(get_bit(test1, 2));
    ASSERT(!get_bit(test1, 3));
    
    uchar test2[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    
    ASSERT(get_bit(test2, 18));
    ASSERT(!get_bit(test2, 31));
    ASSERT(!get_bit(test2, 47));
    ASSERT(get_bit(test2, 62));
}

void test_get_range() {
    uchar test1[] = {0xAA, 0xAA, 0xAA, 0xAA};
    
    ASSERT(get_range(test1, 0, 5) == 42);
    ASSERT(get_range(test1, 16, 31) == 43690);
    
    uchar test2[] = {0x00, 0x00, 0x00, 0x00};
    
    ASSERT(get_range(test2, 0, 7) == 0);
    ASSERT(get_range(test2, 0, 31) == 0);
    
    uchar test3[] = {0xFF, 0xFF, 0xFF, 0xFF};
    
    ASSERT(get_range(test3, 3, 5) == 7);
    ASSERT(get_range(test3, 15, 29) == 32767);
}

void test_get_signed_range() {
    uchar test1[] = {0xAA, 0xAA, 0xAA, 0xAA};
    
    ASSERT(get_signed_range(test1, 0, 7) == -86);
    ASSERT(get_signed_range(test1, 17, 31) == 0x2AAA);
}

void test_btol() {
    uchar test1[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test1) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test1) == 0x0102030405060708);
    
    char test2[8] = {8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT(btol<BIG>(test2) == 0x0807060504030201);
    ASSERT(btol<LITTLE>(test2) == 0x0102030405060708);
}

void test_btoi() {
    uchar test1[4] = {8, 7, 6, 5};
    ASSERT(btoi<BIG>(test1) == 0x08070605);
    ASSERT(btoi<LITTLE>(test1) == 0x05060708);
    
    char test2[4] = {8, 7, 6, 5};
    ASSERT(btoi<BIG>(test2) == 0x08070605);
    ASSERT(btoi<LITTLE>(test2) == 0x05060708);
}

void test_btos() {
    uchar test1[2] = {8, 7};
    ASSERT(btos<BIG>(test1) == 0x0807);
    ASSERT(btos<LITTLE>(test1) == 0x0708);
    
    char test2[2] = {8, 7};
    ASSERT(btos<BIG>(test2) == 0x0807);
    ASSERT(btos<LITTLE>(test2) == 0x0708);
}

void test_btoc() {
    uchar test1[1] = {8};
    ASSERT(btoc<BIG>(test1) == 0x08);
    ASSERT(btoc<LITTLE>(test1) == 0x08);
    
    char test2[1] = {1};
    ASSERT(btoc<BIG>(test2) == 0x01);
    ASSERT(btoc<LITTLE>(test2) == 0x01);
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
    
    slong test3 = 0xFFFEFDFCFBFAF9F8;
    char expected3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    ASSERT(compare(ltob<BIG>(test3, 8), expected3, 8));
    ASSERT(compare(ltob<LITTLE>(test3, 8), reverse(expected3, 8), 8));
    
    slong test4 = 0x0;
    char expected4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    ASSERT(compare(ltob<BIG>(test4, 8), expected4, 8));
    ASSERT(compare(ltob<LITTLE>(test4, 8), reverse(expected4, 8), 8));
}

void test_itob() {
    uint test1 = 0xFFFEFDFC;
    uchar expected1[4] = {255, 254, 253, 252};
    ASSERT(compare(itob<BIG>(test1, 4), expected1, 4));
    ASSERT(compare(itob<LITTLE>(test1, 4), reverse(expected1, 4), 4));
    
    uint test2 = 0x0;
    uchar expected2[4] = {0, 0, 0, 0};
    ASSERT(compare(itob<BIG>(test2, 4), expected2, 4));
    ASSERT(compare(itob<LITTLE>(test2, 4), reverse(expected2, 4), 4));
    
    int test3 = 0xFFFEFDFC;
    char expected3[4] = {-1, -2, -3, -4};
    ASSERT(compare(itob<BIG>(test3, 4), expected3, 4));
    ASSERT(compare(itob<LITTLE>(test3, 4), reverse(expected3, 4), 4));
    
    int test4 = 0x0;
    char expected4[4] = {0, 0, 0, 0};
    ASSERT(compare(itob<BIG>(test4, 4), expected4, 4));
    ASSERT(compare(itob<LITTLE>(test4, 4), reverse(expected4, 4), 4));
}

void test_stob() {
    ushort test1 = 0xFFFE;
    uchar expected1[2] = {255, 254};
    ASSERT(compare(stob<BIG>(test1, 2), expected1, 2));
    ASSERT(compare(stob<LITTLE>(test1, 2), reverse(expected1, 2), 2));
    
    ushort test2 = 0x0;
    uchar expected2[2] = {0, 0};
    ASSERT(compare(stob<BIG>(test2, 2), expected2, 2));
    ASSERT(compare(stob<LITTLE>(test2, 2), reverse(expected2, 2), 2));
    
    short test3 = (short)0xFFFE;
    char expected3[2] = {-1, -2};
    ASSERT(compare(stob<BIG>(test3, 2), expected3, 2));
    ASSERT(compare(stob<LITTLE>(test3, 2), reverse(expected3, 2), 2));
    
    short test4 = 0x0;
    char expected4[2] = {0, 0};
    ASSERT(compare(stob<BIG>(test4, 2), expected4, 2));
    ASSERT(compare(stob<LITTLE>(test4, 2), reverse(expected4, 2), 2));
}

void test_ctob() {
    uchar test1 = 0xFF;
    uchar expected1[1] = {255};
    ASSERT(compare(ctob<BIG>(test1, 1), expected1, 1));
    ASSERT(compare(ctob<LITTLE>(test1, 1), reverse(expected1, 1), 1));
    
    uchar test2 = 0x0;
    uchar expected2[1] = {0};
    ASSERT(compare(ctob<BIG>(test2, 1), expected2, 1));
    ASSERT(compare(ctob<LITTLE>(test2, 1), reverse(expected2, 1), 1));
    
    char test3 = (char)0xFF;
    char expected3[1] = {-1};
    ASSERT(compare(ctob<BIG>(test3, 1), expected3, 1));
    ASSERT(compare(ctob<LITTLE>(test3, 1), reverse(expected3, 1), 1));
    
    char test4 = 0x0;
    char expected4[1] = {0};
    ASSERT(compare(ctob<BIG>(test4, 1), expected4, 1));
    ASSERT(compare(ctob<LITTLE>(test4, 1), reverse(expected4, 1), 1));
    
}

void run_bytes_tests() {
    TEST(test_get_bit)
    TEST(test_get_range)
    TEST(test_get_signed_range)
    
    TEST(test_btol)
    TEST(test_btoi)
    TEST(test_btos)
    TEST(test_btoc)
    
    TEST(test_ltob)
    TEST(test_itob)
    TEST(test_stob)
    TEST(test_ctob)
}


#include "test_arrays.h"
#include "tests/test.h"
#include "utils/arrays.h"

using namespace util;

void test_compare() {
    uchar test1[4] = {1, 2, 3, 4};
    uchar test2[4] = {1, 2, 3, 4};
    uchar test3[4] = {4, 3, 2, 1};
    ASSERT(compare(test1, test2, 4));
    ASSERT(!compare(test1, test3, 4));
}

void test_compare_2D() {
    uchar **test1 = new uchar*[3];
    for (uint i = 0; i < 3; ++i) {
        test1[i] = new uchar[3] {1, 2, 3};
    }
    uchar **test2 = new uchar*[3];
    for (uint i = 0; i < 3; ++i) {
        test2[i] = new uchar[3] {1, 2, 3};
    }
    uchar **test3 = new uchar*[3];
    for (uint i = 0; i < 3; ++i) {
        test3[i] = new uchar[3] {3, 2, 1};
    }
    ASSERT(compare_2D(test1, test2, 3));
    ASSERT(!compare_2D(test1, test3, 3));
}

void test_copy() {
    uchar test1[4] = {1, 2, 3, 4};
    uchar test2[4];
    copy(test1, test2, 4);
    ASSERT(compare(test1, test2, 4));
    char test3[4] = {4, 3, 2, 1};
    char test4[4];
    copy(test3, test4, 4);
    ASSERT(compare(test3, test4, 4));
}

void test_copy_2D() {
    uchar **test1 = new uchar*[3];
    for (uint i = 0; i < 3; ++i) {
        test1[i] = new uchar[3] {1, 2, 3};
    }
    uchar **test2 = new uchar*[3];
    for (uint i = 0; i < 3; ++i) {
        test2[i] = new uchar[3]();
    }
    ASSERT(!compare_2D(test1, test2, 3));
    copy_2D(test1, test2, 3);
    ASSERT(compare_2D(test1, test2, 3));
}

void test_reverse_arr() {
    uchar test1[4] = {1, 2, 3, 4};
    uchar result1[4] = {4, 3, 2, 1};
    uchar result2[4] = {1, 2, 3, 4};
    ASSERT(compare(reverse(test1, 4), result1, 4));
    reverse(test1, 4);
    ASSERT(compare(test1, result2, 4));
}

void test_convert() {
    uchar test1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uchar result1[8] = {4, 3, 2, 1, 8, 7, 6, 5};
    endian_convert(test1, 8);
    ASSERT(compare(test1, result1, 8));
    uchar test2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uchar result2[8] = {2, 1, 4, 3, 6, 5, 8, 7};
    endian_convert(test2, 8, 2);
    ASSERT(compare(test2, result2, 8));
}

void run_arrays_tests() {
    TEST(test_compare)
    TEST(test_compare_2D)
    TEST(test_copy)
    TEST(test_copy_2D)
    TEST(test_reverse_arr)
    TEST(test_convert)
}
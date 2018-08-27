
#include "test_strmanip.h"
#include "utils/strmanip.h"

using namespace util;

void test_reverse_str() {
    std::string test = "abcd";
    ASSERT(reverse(test) == "dcba");
}

void test_starts_with() {
    std::string test1 = "abcdefg";
    ASSERT(starts_with(test1, "abc"));
    ASSERT(!starts_with(test1, "acd"));
}

void test_ends_with() {
    std::string test1 = "abc.txt";
    ASSERT(ends_with(test1, ".txt"));
    ASSERT(!ends_with(test1, "png"));
}

void TestToHex::run() {
    TEST_METHOD(from_bytes)
    TEST_METHOD(from_long)
    TEST_METHOD(from_int)
    TEST_METHOD(from_short)
    TEST_METHOD(from_char)
}

void TestToHex::from_bytes() {
    uchar bytes1[5] = {12, 13, 14, 15, 16};
    ASSERT(btoh<BIG>(bytes1, 5) == "0x0C0D0E0F10");
    ASSERT(btoh<BIG>(bytes1, 5, false) == "0C0D0E0F10");
    ASSERT(btoh<LITTLE>(bytes1, 5) == "0x100F0E0D0C");
    ASSERT(btoh<LITTLE>(bytes1, 5, false) == "100F0E0D0C");
    
    char bytes2[5] = {16, -1, -2, 5, 36};
    ASSERT(btoh<BIG>(bytes2, 5) == "0x10FFFE0524");
    ASSERT(btoh<BIG>(bytes2, 5, false) == "10FFFE0524");
    ASSERT(btoh<LITTLE>(bytes2, 5) == "0x2405FEFF10");
    ASSERT(btoh<LITTLE>(bytes2, 5, false) == "2405FEFF10");
}

void TestToHex::from_long() {
    ulong test1 = 1;
    ASSERT(ltoh<BIG>(test1) == "0x0000000000000001");
    ASSERT(ltoh<LITTLE>(test1) == "0x0100000000000000");
    
    ulong test2 = 111111111257243578;
    ASSERT(ltoh<BIG>(test2) == "0x018ABEF78D163FBA");
    ASSERT(ltoh<LITTLE>(test2) == "0xBA3F168DF7BE8A01");
    
    long test3 = 5;
    ASSERT(ltoh<BIG>(test3) == "0x0000000000000005");
    ASSERT(ltoh<LITTLE>(test3) == "0x0500000000000000");
    
    long test4 = -587342;
    ASSERT(ltoh<BIG>(test4) == "-0x000000000008F64E");
    ASSERT(ltoh<LITTLE>(test4) == "-0x4EF6080000000000");
}

void TestToHex::from_int() {
    uint test1 = 1;
    ASSERT(itoh<BIG>(test1) == "0x00000001");
    ASSERT(itoh<LITTLE>(test1) == "0x01000000");
    
    uint test2 = 675323;
    ASSERT(itoh<BIG>(test2) == "0x000A4DFB");
    ASSERT(itoh<LITTLE>(test2) == "0xFB4D0A00");
    
    int test3 = 48;
    ASSERT(itoh<BIG>(test3) == "0x00000030");
    ASSERT(itoh<LITTLE>(test3) == "0x30000000");
    
    int test4 = -275;
    ASSERT(itoh<BIG>(test4) == "-0x00000113");
    ASSERT(itoh<LITTLE>(test4) == "-0x13010000");
}

void TestToHex::from_short() {
    // TODO
    throw testing::skip_test();
}

void TestToHex::from_char() {
    // TODO
    throw testing::skip_test();
}

void test_char_format() {
    // TODO
    throw testing::skip_test();
}

void run_strmanip_tests() {
    TEST(test_reverse_str)
    TEST(test_starts_with)
    TEST(test_ends_with)
    TEST_CLASS(TestToHex)
    TEST(test_char_format)
}

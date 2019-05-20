
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
    ASSERT(btoh<BIG>(bytes1, 5) == "0xC0D0E0F10");
    ASSERT(btoh<BIG>(bytes1, 5, false) == "C0D0E0F10");
    ASSERT(btoh<BIG>(bytes1, 5, true, true) == "0x0C0D0E0F10");
    ASSERT(btoh<LITTLE>(bytes1, 5) == "0x100F0E0D0C");
    ASSERT(btoh<LITTLE>(bytes1, 5, false) == "100F0E0D0C");
    
    char bytes2[5] = {16, -1, -2, 5, 36};
    ASSERT(btoh<BIG>(bytes2, 5) == "0x10FFFE0524");
    ASSERT(btoh<BIG>(bytes2, 5, false) == "10FFFE0524");
    ASSERT(btoh<LITTLE>(bytes2, 5) == "0x2405FEFF10");
    ASSERT(btoh<LITTLE>(bytes2, 5, false) == "2405FEFF10");
    
    uchar bytes3[1] = {0};
    ASSERT(btoh<BIG>(bytes3, 1) == "0x0");
    ASSERT(btoh<BIG>(bytes3, 1, false) == "0");
    ASSERT(btoh<BIG>(bytes3, 1, true, true) == "0x00");
    ASSERT(btoh<LITTLE>(bytes3, 1) == "0x0");
    ASSERT(btoh<LITTLE>(bytes3, 1, false) == "0");
    ASSERT(btoh<LITTLE>(bytes3, 1, true, true) == "0x00");
    
    char bytes4[1] = {0};
    ASSERT(btoh<BIG>(bytes4, 1) == "0x0");
    ASSERT(btoh<BIG>(bytes4, 1, false) == "0");
    ASSERT(btoh<BIG>(bytes4, 1, true, true) == "0x00");
    ASSERT(btoh<LITTLE>(bytes4, 1) == "0x0");
    ASSERT(btoh<LITTLE>(bytes4, 1, false) == "0");
    ASSERT(btoh<LITTLE>(bytes4, 1, true, true) == "0x00");
}

void TestToHex::from_long() {
    ulong test1 = 1;
    ASSERT(ltoh<BIG>(test1) == "0x1");
    ASSERT(ltoh<BIG>(test1, false) == "1");
    ASSERT(ltoh<BIG>(test1, true, true) == "0x0000000000000001");
    ASSERT(ltoh<LITTLE>(test1) == "0x100000000000000");
    ASSERT(ltoh<LITTLE>(test1, false) == "100000000000000");
    ASSERT(ltoh<LITTLE>(test1, true, true) == "0x0100000000000000");
    
    ulong test2 = 111111111257243578;
    ASSERT(ltoh<BIG>(test2) == "0x18ABEF78D163FBA");
    ASSERT(ltoh<BIG>(test2, false) == "18ABEF78D163FBA");
    ASSERT(ltoh<BIG>(test2, true, true) == "0x018ABEF78D163FBA");
    ASSERT(ltoh<LITTLE>(test2) == "0xBA3F168DF7BE8A01");
    ASSERT(ltoh<LITTLE>(test2, false) == "BA3F168DF7BE8A01");
    
    slong test3 = 5;
    ASSERT(ltoh<BIG>(test3) == "0x5");
    ASSERT(ltoh<BIG>(test3, false) == "5");
    ASSERT(ltoh<BIG>(test3, true, true) == "0x0000000000000005");
    ASSERT(ltoh<LITTLE>(test3) == "0x500000000000000");
    ASSERT(ltoh<LITTLE>(test3, false) == "500000000000000");
    ASSERT(ltoh<LITTLE>(test3, true, true) == "0x0500000000000000");
    
    slong test4 = -587342;
    ASSERT(ltoh<BIG>(test4) == "-0x8F64E");
    ASSERT(ltoh<BIG>(test4, false) == "-8F64E");
    ASSERT(ltoh<BIG>(test4, true, true) == "-0x000000000008F64E");
    ASSERT(ltoh<LITTLE>(test4) == "-0x4EF6080000000000");
    ASSERT(ltoh<LITTLE>(test4, false) == "-4EF6080000000000");
}

void TestToHex::from_int() {
    uint test1 = 1;
    ASSERT(itoh<BIG>(test1) == "0x1");
    ASSERT(itoh<BIG>(test1, false) == "1");
    ASSERT(itoh<BIG>(test1, true, true) == "0x00000001");
    ASSERT(itoh<LITTLE>(test1) == "0x1000000");
    ASSERT(itoh<LITTLE>(test1, false) == "1000000");
    ASSERT(itoh<LITTLE>(test1, true, true) == "0x01000000");
    
    uint test2 = 675323;
    ASSERT(itoh<BIG>(test2) == "0xA4DFB");
    ASSERT(itoh<BIG>(test2, false) == "A4DFB");
    ASSERT(itoh<BIG>(test2, true, true) == "0x000A4DFB");
    ASSERT(itoh<LITTLE>(test2) == "0xFB4D0A00");
    ASSERT(itoh<LITTLE>(test2, false) == "FB4D0A00");
    
    int test3 = 48;
    ASSERT(itoh<BIG>(test3) == "0x30");
    ASSERT(itoh<BIG>(test3, false) == "30");
    ASSERT(itoh<BIG>(test3, true, true) == "0x00000030");
    ASSERT(itoh<LITTLE>(test3) == "0x30000000");
    ASSERT(itoh<LITTLE>(test3, false) == "30000000");
    
    int test4 = -275;
    ASSERT(itoh<BIG>(test4) == "-0x113");
    ASSERT(itoh<BIG>(test4, false) == "-113");
    ASSERT(itoh<BIG>(test4, true, true) == "-0x00000113");
    ASSERT(itoh<LITTLE>(test4) == "-0x13010000");
    ASSERT(itoh<LITTLE>(test4, false) == "-13010000");
}

void TestToHex::from_short() {
    ushort test1 = 1;
    ASSERT(stoh<BIG>(test1) == "0x1");
    ASSERT(stoh<BIG>(test1, false) == "1");
    ASSERT(stoh<BIG>(test1, true, true) == "0x0001");
    ASSERT(stoh<LITTLE>(test1) == "0x100");
    ASSERT(stoh<LITTLE>(test1, false) == "100");
    ASSERT(stoh<LITTLE>(test1, true, true) == "0x0100");
    
    ushort test2 = 63535;
    ASSERT(stoh<BIG>(test2) == "0xF82F");
    ASSERT(stoh<BIG>(test2, false) == "F82F");
    ASSERT(stoh<LITTLE>(test2) == "0x2FF8");
    ASSERT(stoh<LITTLE>(test2, false) == "2FF8");
    
    short test3 = 65;
    ASSERT(stoh<BIG>(test3) == "0x41");
    ASSERT(stoh<BIG>(test3, false) == "41");
    ASSERT(stoh<BIG>(test3, true, true) == "0x0041");
    ASSERT(stoh<LITTLE>(test3) == "0x4100");
    ASSERT(stoh<LITTLE>(test3, false) == "4100");
    
    short test4 = -546;
    ASSERT(stoh<BIG>(test4) == "-0x222");
    ASSERT(stoh<BIG>(test4, false) == "-222");
    ASSERT(stoh<BIG>(test4, true, true) == "-0x0222");
    ASSERT(stoh<LITTLE>(test4) == "-0x2202");
    ASSERT(stoh<LITTLE>(test4, false) == "-2202");
}

void TestToHex::from_char() {
    uchar test1 = 1;
    ASSERT(ctoh<BIG>(test1) == "0x1");
    ASSERT(ctoh<BIG>(test1, false) == "1");
    ASSERT(ctoh<BIG>(test1, true, true) == "0x01");
    ASSERT(ctoh<LITTLE>(test1) == "0x1");
    ASSERT(ctoh<LITTLE>(test1, false) == "1");
    ASSERT(ctoh<LITTLE>(test1, true, true) == "0x01");
    
    uchar test2 = 212;
    ASSERT(ctoh<BIG>(test2) == "0xD4");
    ASSERT(ctoh<BIG>(test2, false) == "D4");
    ASSERT(ctoh<LITTLE>(test2) == "0xD4");
    ASSERT(ctoh<LITTLE>(test2, false) == "D4");
    
    char test3 = 83;
    ASSERT(ctoh<BIG>(test3) == "0x53");
    ASSERT(ctoh<BIG>(test3, false) == "53");
    ASSERT(ctoh<LITTLE>(test3) == "0x53");
    ASSERT(ctoh<LITTLE>(test3, false) == "53");
    
    char test4 = -115;
    ASSERT(ctoh<BIG>(test4) == "-0x73");
    ASSERT(ctoh<BIG>(test4, false) == "-73");
    ASSERT(ctoh<LITTLE>(test4) == "-0x73");
    ASSERT(ctoh<LITTLE>(test4, false) == "-73");
}


// TODO: Add no prefix to from_ tests
void run_strmanip_tests() {
    TEST(test_reverse_str)
    TEST(test_starts_with)
    TEST(test_ends_with)
    TEST_CLASS(TestToHex)
}


#include <sstream>
#include "test_io.h"
#include "utils/io.h"

void TestReadIO::test_next_ulong() {
    std::istringstream input("\x01\x02\x03\x04\x05\x06\x07\x08\x01\x02\x03\x04\x05\x06\x07\x08");
    ASSERT(util::next_ulong<BIG>(input) == 0x0102030405060708);
    ASSERT(util::next_ulong<LITTLE>(input) == 0x0807060504030201);
}

void TestReadIO::test_next_uint() {
    std::istringstream input("\x01\x02\x03\x04\x05\x06\x07\x08");
    ASSERT(util::next_uint<BIG>(input) == 0x01020304);
    ASSERT(util::next_uint<LITTLE>(input) == 0x08070605);
}

void TestReadIO::test_next_ushort() {
    std::istringstream input("\x01\x02\x03\x04");
    ASSERT(util::next_ushort<BIG>(input) == 0x0102);
    ASSERT(util::next_ushort<LITTLE>(input) == 0x0403);
}

void TestReadIO::test_next_uchar() {
    std::istringstream input("\xFF\x02");
    ASSERT(util::next_uchar<BIG>(input) == 0xFF);
    ASSERT(util::next_uchar<LITTLE>(input) == 0x02);
}

void TestReadIO::test_next_long() {
    throw testing::skip_test();
}

void TestReadIO::test_next_int() {
    throw testing::skip_test();
}

void TestReadIO::test_next_short() {
    throw testing::skip_test();
}

void TestReadIO::test_next_char() {
    throw testing::skip_test();
}

void TestReadIO::test_next_float() {
    std::istringstream input(std::string("\x3f\x80\x00\x00\x80\x00\x70\x47", 8));
    ASSERT(util::next_float<BIG>(input) == 1.f);
    ASSERT(util::next_float<LITTLE>(input) == 61440.5f);
}

void TestReadIO::test_next_double() {
    throw testing::skip_test();
}

void TestReadIO::run() {
    TEST_METHOD(test_next_ulong)
    TEST_METHOD(test_next_uint)
    TEST_METHOD(test_next_ushort)
    TEST_METHOD(test_next_uchar)
    TEST_METHOD(test_next_long)
    TEST_METHOD(test_next_int)
    TEST_METHOD(test_next_short)
    TEST_METHOD(test_next_char)
    TEST_METHOD(test_next_float)
    TEST_METHOD(test_next_double)
}


void TestWriteIO::test_write_ulong() {
    std::ostringstream output;
    util::write_ulong<BIG>(output, 0x0102030405060708);
    util::write_ulong<LITTLE>(output, 0x0102030405060708);
    ASSERT(output.str() == "\x01\x02\x03\x04\x05\x06\x07\x08\x08\x07\x06\x05\x04\x03\x02\x01");
}

void TestWriteIO::test_write_uint() {
    std::ostringstream output;
    util::write_uint<BIG>(output, 0x01020304);
    util::write_uint<LITTLE>(output, 0x08070605);
    ASSERT(output.str() == "\x01\x02\x03\x04\x05\x06\x07\x08");
}

void TestWriteIO::test_write_ushort() {
    std::ostringstream output;
    util::write_ushort<BIG>(output, 0x0102);
    util::write_ushort<LITTLE>(output, 0x0403);
    ASSERT(output.str() == "\x01\x02\x03\x04");
}

void TestWriteIO::test_write_uchar() {
    std::ostringstream output;
    util::write_uchar<BIG>(output, 0xFF);
    util::write_uchar<LITTLE>(output, 0x02);
    ASSERT(output.str() == "\xFF\x02");
}

void TestWriteIO::test_write_long() {
    throw testing::skip_test();
}

void TestWriteIO::test_write_int() {
    throw testing::skip_test();
}

void TestWriteIO::test_write_short() {
    throw testing::skip_test();
}

void TestWriteIO::test_write_char() {
    throw testing::skip_test();
}

void TestWriteIO::test_write_float() {
    std::ostringstream output;
    util::write_float<BIG>(output, 1.f);
    util::write_float<LITTLE>(output, 61440.5f);
    ASSERT(output.str() == std::string("\x3f\x80\x00\x00\x80\x00\x70\x47", 8));
}

void TestWriteIO::test_write_double() {
    throw testing::skip_test();
}

void TestWriteIO::run() {
    TEST_METHOD(test_write_ulong)
    TEST_METHOD(test_write_uint)
    TEST_METHOD(test_write_ushort)
    TEST_METHOD(test_write_uchar)
    TEST_METHOD(test_write_long)
    TEST_METHOD(test_write_int)
    TEST_METHOD(test_write_short)
    TEST_METHOD(test_write_char)
    TEST_METHOD(test_write_float)
    TEST_METHOD(test_write_double)
}


void run_io_tests() {
    TEST_CLASS(TestReadIO)
    TEST_CLASS(TestWriteIO)
}


#include <sstream>
#include "test_io.h"
#include "utils/io.h"


void TestReadIO::test_next_ulong() {
    std::istringstream input("\x01\x02\x03\x04\x05\x06\x07\x08\x01\x02\x03\x04\x05\x06\x07\x08");
    ASSERT(util::next_ulong<Endian::BIG>(input) == 0x0102030405060708);
    ASSERT(util::next_ulong<Endian::LITTLE>(input) == 0x0807060504030201);
}

void TestReadIO::test_next_uint() {
    std::istringstream input("\x01\x02\x03\x04\x05\x06\x07\x08");
    ASSERT(util::next_uint<Endian::BIG>(input) == 0x01020304);
    ASSERT(util::next_uint<Endian::LITTLE>(input) == 0x08070605);
}

void TestReadIO::test_next_ushort() {
    std::istringstream input("\x01\x02\x03\x04");
    ASSERT(util::next_ushort<Endian::BIG>(input) == 0x0102);
    ASSERT(util::next_ushort<Endian::LITTLE>(input) == 0x0403);
}

void TestReadIO::test_next_uchar() {
    std::istringstream input("\xFF\x02");
    ASSERT(util::next_uchar<Endian::BIG>(input) == 0xFF);
    ASSERT(util::next_uchar<Endian::LITTLE>(input) == 0x02);
}

void TestReadIO::test_next_long() {
    std::istringstream input("\xFF\xFE\xFD\xFC\xFB\xFA\xF9\xF8\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF");
    
    ASSERT(util::next_long<Endian::BIG>(input) == -283686952306184L);
    ASSERT(util::next_long<Endian::LITTLE>(input) == -283686952306184L);
}

void TestReadIO::test_next_int() {
    std::istringstream input(std::string("\xFF\xFF\xFF\xFE\x01\x00\x00\x00", 8));
    
    ASSERT(util::next_int<Endian::BIG>(input) == -2);
    ASSERT(util::next_int<Endian::LITTLE>(input) == 1);
}

void TestReadIO::test_next_short() {
    std::istringstream input(std::string("\xFF\x00\x00\xFF\x00\x01\x01\x00", 8));
    ASSERT(util::next_short<Endian::BIG>(input) == -256);
    ASSERT(util::next_short<Endian::LITTLE>(input) == -256);
    ASSERT(util::next_short<Endian::BIG>(input) == 1);
    ASSERT(util::next_short<Endian::LITTLE>(input) == 1);
}

void TestReadIO::test_next_char() {
    std::istringstream input("\xFF\x02");
    ASSERT(util::next_char<Endian::BIG>(input) == -1);
    ASSERT(util::next_char<Endian::LITTLE>(input) == 2);
}

void TestReadIO::test_next_float() {
    std::istringstream input(std::string("\x3f\x80\x00\x00\x80\x00\x70\x47", 8));
    ASSERT(util::next_float<Endian::BIG>(input) == 1.f);
    ASSERT(util::next_float<Endian::LITTLE>(input) == 61440.5f);
}

void TestReadIO::test_next_double() {
    std::istringstream input(std::string("\x3F\xF0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x00\xEE\x40", 16));
    ASSERT(util::next_double<Endian::BIG>(input) == 1.);
    ASSERT(util::next_double<Endian::LITTLE>(input) == 61440.5);
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
    util::write_ulong<Endian::BIG>(output, 0x0102030405060708);
    util::write_ulong<Endian::LITTLE>(output, 0x0102030405060708);
    ASSERT(output.str() == "\x01\x02\x03\x04\x05\x06\x07\x08\x08\x07\x06\x05\x04\x03\x02\x01");
}

void TestWriteIO::test_write_uint() {
    std::ostringstream output;
    util::write_uint<Endian::BIG>(output, 0x01020304);
    util::write_uint<Endian::LITTLE>(output, 0x08070605);
    ASSERT(output.str() == "\x01\x02\x03\x04\x05\x06\x07\x08");
}

void TestWriteIO::test_write_ushort() {
    std::ostringstream output;
    util::write_ushort<Endian::BIG>(output, 0x0102);
    util::write_ushort<Endian::LITTLE>(output, 0x0403);
    ASSERT(output.str() == "\x01\x02\x03\x04");
}

void TestWriteIO::test_write_uchar() {
    std::ostringstream output;
    util::write_uchar<Endian::BIG>(output, 0xFF);
    util::write_uchar<Endian::LITTLE>(output, 0x02);
    ASSERT(output.str() == "\xFF\x02");
}

void TestWriteIO::test_write_long() {
    std::ostringstream output;
    util::write_long<Endian::BIG>(output, -283686952306184l);
    util::write_long<Endian::LITTLE>(output, -283686952306184l);
    ASSERT(output.str() == "\xFF\xFE\xFD\xFC\xFB\xFA\xF9\xF8\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF");
}

void TestWriteIO::test_write_int() {
    std::ostringstream output;
    util::write_int<Endian::BIG>(output, -2);
    util::write_int<Endian::LITTLE>(output, 1);
    ASSERT(output.str() == std::string("\xFF\xFF\xFF\xFE\x01\x00\x00\x00", 8));
}

void TestWriteIO::test_write_short() {
    std::ostringstream output;
    util::write_short<Endian::BIG>(output, -256);
    util::write_short<Endian::LITTLE>(output, -256);
    util::write_short<Endian::BIG>(output, 1);
    util::write_short<Endian::LITTLE>(output, 1);
    ASSERT(output.str() == std::string("\xFF\x00\x00\xFF\x00\x01\x01\x00", 8));
}

void TestWriteIO::test_write_char() {
    std::ostringstream output;
    util::write_char<Endian::BIG>(output, -1);
    util::write_char<Endian::LITTLE>(output, 1);
    ASSERT(output.str() == "\xFF\x01");
}

void TestWriteIO::test_write_float() {
    std::ostringstream output;
    util::write_float<Endian::BIG>(output, 1.f);
    util::write_float<Endian::LITTLE>(output, 61440.5f);
    ASSERT(output.str() == std::string("\x3f\x80\x00\x00\x80\x00\x70\x47", 8));
}

void TestWriteIO::test_write_double() {
    std::ostringstream output;
    util::write_double<Endian::BIG>(output, 1.);
    util::write_double<Endian::LITTLE>(output, 61440.5);
    ASSERT(output.str() == std::string("\x3F\xF0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10\x00\xEE\x40", 16));
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
    TEST(TestReadIO())
    TEST(TestWriteIO())
}

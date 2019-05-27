
#include "at_tests"

class TestReadIO : public testing::AbstractTest {
    
    void test_next_ulong();
    void test_next_uint();
    void test_next_ushort();
    void test_next_uchar();
    void test_next_long();
    void test_next_int();
    void test_next_short();
    void test_next_char();
    void test_next_float();
    void test_next_double();
    
public:
    
    void run();
    
};

class TestWriteIO : public testing::AbstractTest {
    
    void test_write_ulong();
    void test_write_uint();
    void test_write_ushort();
    void test_write_uchar();
    void test_write_long();
    void test_write_int();
    void test_write_short();
    void test_write_char();
    void test_write_float();
    void test_write_double();
    
public:
    
    void run();
    
};

void run_io_tests();

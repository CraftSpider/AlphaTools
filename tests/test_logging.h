#pragma once

#include <streambuf>
#include <sstream>
#include "tests/test.h"

class TestLogger : public testing::AbstractTest{
    
    std::streambuf *old_cout;
    std::ostringstream new_cout;
    std::ostringstream new_cerr;
    
    void clear_logs();
    
    void test_root();
    void test_normal();
    void test_format();
    void test_saving();
    
public:
    
    void before_class() override;
    void run() override;
    void after_class() override;
    
};

void run_logging_tests();

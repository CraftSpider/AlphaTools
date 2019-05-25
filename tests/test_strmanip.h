#pragma once

#include "at_tests"

class TestToHex : public testing::AbstractTest {

public:
    
    void run() override;
    
    void from_bytes();
    void from_long();
    void from_int();
    void from_short();
    void from_char();
    
};

void run_strmanip_tests();

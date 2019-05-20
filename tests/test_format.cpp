
#include <iostream>
#include "at_tests"
#include "utils/strmanip.h"
#include "test_format.h"
#include "format.h"

class Form : public Formattable {
public:
    std::string __format__(std::string spec) const override {
        return "Formatted!";
    }
};

class NoForm {};

void ordinal_format() {
    ASSERT(format("{s1} {s0}", "world", "Hello") == "Hello world");
    ASSERT(format("{i1} == {i}", 100, 200) == "200 == 100");
}

void int_format() {
    ASSERT(format("{i}", 12345) == "12345");
    ASSERT(format("{i:0}", 12345) == "12345");
    
    ASSERT(format("{i:x}", 54321) == "d431");
    ASSERT(format("{i:x0}", 54321) == "0xd431");
    
    ASSERT(format("{i:X}", 54321) == "D431");
    ASSERT(format("{i:X0}", 54321) == "0xD431");
    
    ASSERT(format("{i:o}", 12345) == "30071");
    ASSERT(format("{i:o0}", 12345) == "0o30071");
}

void bytes_format() {
    uchar bytes[] = {0x12, 0x34, 0x56, 0x78, 0x9A};
    
    ASSERT(format("{b:x0,7}", bytes) == "0x12");
    ASSERT(format("{b:X4,11}", bytes) == "0x23");
    
    ASSERT(format("{b:s3,6}", bytes) == "-7");
    ASSERT(format("{b:a3,6}", bytes) == "7");
}

void object_format() {
    Form form = Form();
    NoForm noform = NoForm();
    
    ASSERT(format("{o}", &form) == "Formatted!");
    
    try {
        format("{o}", &noform);
        ASSERT(false, "Formatting unformattable object didn't throw an error");
    } catch (format_error &e) {}
}

void run_format_tests() {
    TEST(ordinal_format)
    TEST(int_format)
    TEST(bytes_format)
    TEST(object_format)
}
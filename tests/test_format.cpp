
#include <iostream>
#include "at_tests"
#include "utils/strmanip.h"
#include "test_format.h"
#include "format.h"

class Form : Formattable {
public:
    std::string __format__(std::string spec) override {
        return "Formatted!";
    }
};

class NoForm {};

void ordinal_format() {
    // TODO: test {0}, {1}, {0} stuff
    throw testing::skip_test();
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

void object_format() {
    Form form = Form();
    NoForm noform = NoForm();
    
    ASSERT(format("{o}", &form) == "Formatted!");
    ASSERT(util::starts_with(format("{o}", &noform), "[[NON-FORMATTABLE OBJECT"));
}

void run_format_tests() {
    TEST(ordinal_format)
    TEST(int_format)
    TEST(object_format)
}
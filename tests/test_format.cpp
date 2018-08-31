
#include <iostream>
#include "at_tests"
#include "test_format.h"
#include "format.h"

class Form : Formattable {
public:
    std::string __format__(std::string spec) {
        return "Formatted!";
    }
};

void ordinal_format() {
    // TODO: test {0}, {1}, {0} stuff
    throw testing::skip_test();
}

void int_format() {
    ASSERT(format("{i}", 12345) == "12345");
    ASSERT(format("{i0}", 12345) == "12345");
    
    ASSERT(format("{ix}", 54321) == "d431");
    ASSERT(format("{ix0}", 54321) == "0xd431");
    
    ASSERT(format("{iX}", 54321) == "D431");
    ASSERT(format("{iX0}", 54321) == "0xD431");
    
    ASSERT(format("{io}", 12345) == "30071");
    ASSERT(format("{io0}", 12345) == "0o30071");
}

void object_format() {
    Form *form = new Form();
    std::cout << format("{o}", form) << std::endl;
    delete form;
    throw testing::skip_test();
}

void run_format_tests() {
    TEST(ordinal_format)
    TEST(int_format)
    TEST(object_format)
}
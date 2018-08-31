
#include <iostream>
#include "at_tests"
#include "test_format.h"
#include "format.h"

class Form : Formattable {
public:
    std::string __format__(std::string spec) override {
        return "Formatted!";
    }
};

void ordinal_format() {
    // TODO: test {0}, {1}, {0} stuff
    throw testing::skip_test();
}

void int_format() {
    throw testing::skip_test();
}

void object_format() {
    Form *form = new Form();
    delete form;
    throw testing::skip_test();
}

void run_format_tests() {
    TEST(ordinal_format)
    TEST(int_format)
}
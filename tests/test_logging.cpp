
#include <iostream>
#include "test_logging.h"
#include "at_tests"
#include "at_logging"

using namespace logging;

void TestLogger::before_class() {
    old_cout = std::cout.rdbuf();
    new_out = std::ostringstream();
    std::cout.rdbuf(new_out.rdbuf());
}

void TestLogger::run() {
    TEST_METHOD(test_root);
    TEST_METHOD(test_normal);
    TEST_METHOD(test_format);
}

void TestLogger::after_class() {
    std::cout.rdbuf(old_cout);
}

void TestLogger::test_root() {}

void TestLogger::test_normal() {}

void TestLogger::test_format() {}

void run_logging_tests() {
    TEST_CLASS(TestLogger)
}
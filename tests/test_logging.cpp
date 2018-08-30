
#include <iostream>
#include "test_logging.h"
#include "at_logging"

using namespace logging;

void TestLogger::before_class() {
    // TODO fix this
    old_cout = std::cout.rdbuf();
    new_out = std::ostringstream();
    std::cout.basic_ios<char>::rdbuf(new_out.rdbuf());
    std::cout << "Test" << std::endl;
}

void TestLogger::after_class() {
    std::cout.rdbuf(old_cout);
}

void TestLogger::run() {
    TEST_METHOD(test_root);
    TEST_METHOD(test_normal);;
    TEST_METHOD(test_format);
}

void TestLogger::test_root() {
    throw testing::skip_test();
}

void TestLogger::test_normal() {
    throw testing::skip_test();
}

void TestLogger::test_format() {
    Logger *root = get_root_logger();
    root->fatal("Test Default");
    std::cerr << new_out.str() << std::endl;
    ASSERT(new_out.str() == "FATAL: Test Default");
    new_out.clear();
    root->set_pattern("%m %l");
    root->info("Test new");
    ASSERT(new_out.str() == "Test new INFO");
    
}

void run_logging_tests() {
    TEST_CLASS(TestLogger)
}
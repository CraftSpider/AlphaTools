
#include <iostream>
#include "test_logging.h"
#include "at_logging"

using namespace logging;

void TestLogger::before_class() {
    // TODO fix this
    old_cout = std::cout.rdbuf();
    new_cout = std::ostringstream();
    new_cerr = std::ostringstream();
    std::cout.basic_ios<char>::rdbuf(new_cout.rdbuf());
    std::cerr.rdbuf(new_cerr.rdbuf());
}

void TestLogger::after_class() {
    std::cout.rdbuf(old_cout);
}

void TestLogger::run() {
    TEST_METHOD(test_root);
    TEST_METHOD(test_normal);
    TEST_METHOD(test_format);
}

void TestLogger::clear_logs() {
    new_cout.clear();
    new_cout.str("");
    new_cerr.clear();
    new_cerr.str("");
}

void TestLogger::test_root() {
    clear_logs();
    
    Logger *root = get_root_logger();
    
    root->fatal("Test handlers");
    ASSERT(new_cout.str() == "FATAL: Test handlers\n");
    ASSERT(new_cerr.str() == "FATAL: Test handlers\n");
    clear_logs();
    
    root->info("Second test");
    ASSERT(new_cout.str() == "INFO: Second test\n");
    ASSERT(new_cerr.str().empty());
    
    clear_logs();
}

void TestLogger::test_normal() {
    clear_logs();
    
    Logger* newlog = get_logger("newlog");
    newlog->info("Propagates");
    ASSERT(new_cout.str() == "INFO: Propagates\n");
    clear_logs();
    
    newlog->set_propagation(false);
    newlog->info("Doesn't propagate");
    ASSERT(new_cout.str().empty());
    clear_logs();
}

void TestLogger::test_format() {
    clear_logs();
    
    Logger *root = get_root_logger();
    root->fatal("Test Default");
    ASSERT(new_cout.str() == "FATAL: Test Default\n");
    clear_logs();
    
    root->set_pattern("%m %l");
    root->info("Test new");
    ASSERT(new_cout.str() == "Test new INFO\n");
    ASSERT(new_cerr.str().empty());
    
    root->set_pattern("%l: %m");
    clear_logs();
}

void run_logging_tests() {
    TEST_CLASS(TestLogger)
}
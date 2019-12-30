
#include <iostream>
#include "test_logging.h"
#include "at_logging"

using namespace logging;

void TestLogger::before_class() {
    old_cout = std::cout.rdbuf();
    old_cerr = std::cerr.rdbuf();
    new_cout = std::ostringstream();
    new_cerr = std::ostringstream();
    std::cout.rdbuf(new_cout.rdbuf());
    std::cerr.rdbuf(new_cerr.rdbuf());
}

void TestLogger::after_class() {
    std::cout.rdbuf(old_cout);
    std::cerr.rdbuf(old_cerr);
}

void TestLogger::before_test(std::string) {
    clear_logs();
}

void TestLogger::after_test(std::string) {
    clear_logs();
}

void TestLogger::run() {
    TEST_METHOD(test_root)
    TEST_METHOD(test_default_level)
    TEST_METHOD(test_normal)
    TEST_METHOD(test_format)
    TEST_METHOD(test_saving)
	TEST_METHOD(test_auto_parent)
}

void TestLogger::clear_logs() {
    new_cout.clear();
    new_cout.str("");
    new_cerr.clear();
    new_cerr.str("");
}

void TestLogger::test_root() {
    Logger *root = get_root_logger();
    
    root->fatal("Test handlers");
    ASSERT(new_cout.str() == "FATAL: Test handlers\n");
    ASSERT(new_cerr.str() == "FATAL: Test handlers\n");
    clear_logs();
    
    root->info("Second test");
    ASSERT(new_cout.str() == "INFO: Second test\n");
    ASSERT(new_cerr.str().empty());
}

void TestLogger::test_default_level() {
    Logger *root = get_root_logger();
    
    root->info("First test");
    ASSERT(root->get_level() == DEFAULT_LOGGER_LEVEL);
    ASSERT(new_cout.str() == "INFO: First test\n");
    clear_logs();
    
    set_default_level(FATAL);
    
    root->info("Second test");
    ASSERT(root->get_level() == FATAL);
    ASSERT(new_cout.str().empty());
    
    set_default_level(DEFAULT_LOGGER_LEVEL);
    
    ASSERT(root->get_level() == DEFAULT_LOGGER_LEVEL);
}

void TestLogger::test_normal() {
    Logger* newlog = get_logger("newlog");
    newlog->info("Propagates");
    ASSERT(new_cout.str() == "INFO: Propagates\n");
    clear_logs();
    
    newlog->set_propagation(false);
    newlog->info("Doesn't propagate");
    ASSERT(new_cout.str().empty());
}

void TestLogger::test_format() {
    Logger *root = get_root_logger();
    root->fatal("Test Default");
    ASSERT(new_cout.str() == "FATAL: Test Default\n");
    clear_logs();
    
    root->set_pattern("%m %l");
    root->info("Test new");
    ASSERT(new_cout.str() == "Test new INFO\n");
    ASSERT(new_cerr.str().empty());
    
    root->set_pattern("%l: %m");
}

void TestLogger::test_saving() {
    Logger *test1 = get_logger("test");
    Logger *test2 = get_logger("test");
    
    ASSERT(test1 == test2);
}

void TestLogger::test_auto_parent() {
	Logger *test1 = get_logger("parent.test1");
	Logger *test2 = get_logger("parent.test2", true);
	Logger *parent = get_logger("parent");
	
	ASSERT(test1->get_parent() == test2->get_parent());
	ASSERT(test1->get_parent() == parent);
	
	Logger *test3 = get_logger("parent.test3", false);
	
	ASSERT(test3->get_parent() == get_root_logger());
	ASSERT(test3->get_parent() != parent);
	
	Logger *test4 = get_logger("test4");
	ASSERT(test4->get_parent() == get_root_logger());
	
	Logger *root = get_logger("root");
	ASSERT(root->get_parent() == nullptr);
}

void run_logging_tests() {
    TEST(TestLogger())
}

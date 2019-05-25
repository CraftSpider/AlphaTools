
#include "at_tests"
#include "test_test.h"

void test_assert() {
    testing::assert(true);
}

void test_assert_equal() {
    testing::assert_equal(5, 5);
    testing::assert_equal(std::string("test string"), std::string("test string"));
    
    int val1 = 5;
    int val2 = 5;
    testing::assert_equal(&val1, &val2);
    std::string val3 = "test string";
    std::string val4 = "test string";
    testing::assert_equal(&val3, &val4);
}

void test_assert_not_equal() {
    testing::assert_not_equal(10, 5);
    testing::assert_not_equal(std::string("Hello world"), std::string("Blahblah"));
    
    int val1 = 10;
    int val2 = 6;
    testing::assert_not_equal(&val1, &val2);
    std::string val3 = "Hello world";
    std::string val4 = "Blahblah";
    testing::assert_not_equal(&val3, &val4);
}

void test_fail() {
    try {
        testing::fail();
        throw testing::assertion_failure("");
    } catch (testing::assertion_failure &e) {}
}

void _throws() {
    throw std::runtime_error("Test error");
}

void _noop() {}

void test_assert_throws() {
    testing::assert_throws<std::runtime_error>(_throws);
    
    try {
        testing::assert_throws<std::length_error>(_noop);
        testing::fail();
    } catch (testing::assertion_failure &e) {}
}

void run_test_tests() {
    TEST(test_assert)
    TEST(test_assert_equal)
    TEST(test_assert_not_equal)
    TEST(test_fail)
    TEST(test_assert_throws)
}

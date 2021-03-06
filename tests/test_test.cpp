
#include <fstream>
#include "at_tests"
#include "test_test.h"


void test_assert() {
    testing::assert(true);
    
    bool fail = false;
    
    try {
        testing::assert(false);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("Assertion didn't fail when given a false value");
    }
}


void test_assert_macro() {
    ASSERT(true);
    
    bool fail = false;
    
    try {
        ASSERT(false);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("ASSERT macro didn't fail when given a false value");
    }
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

void test_assert_equal_macro() {
    ASSERT_EQ(5, 5);
    ASSERT_EQ(std::string("test string"), std::string("test string"));
    
    int val1 = 5;
    int val2 = 5;
    ASSERT_EQ(&val1, &val2);
    std::string val3 = "test string";
    std::string val4 = "test string";
    ASSERT_EQ(&val3, &val4);
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

void test_assert_not_equal_macro() {
    ASSERT_NEQ(10, 5);
    ASSERT_NEQ(std::string("Hello world"), std::string("Blahblah"));
    
    int val1 = 10;
    int val2 = 6;
    ASSERT_NEQ(&val1, &val2);
    std::string val3 = "Hello world";
    std::string val4 = "Blahblah";
    ASSERT_NEQ(&val3, &val4);
}

void test_assert_files_equal() {
    std::fstream file1("./resources/test1.txt");
    std::fstream file2("./resources/test2.txt");
    std::fstream file3("./resources/test3.txt");
    
    testing::assert_files_equal(file1, file2, "Equal files compared different");
    
    bool fail = false;
    try {
        testing::assert_files_equal(file1, file3);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("Different files compared equal");
    }
}

void test_assert_files_not_equal() {
    std::fstream file1("./resources/test1.txt");
    std::fstream file2("./resources/test2.txt");
    std::fstream file3("./resources/test3.txt");
    
    testing::assert_files_not_equal(file1, file3, "Different files compared equal");
    
    bool fail = false;
    try {
        testing::assert_files_not_equal(file1, file2);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("Equal files compared different");
    }
}

void test_fail() {
    bool fail = false;
    try {
        testing::fail();
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        throw testing::assertion_failure("Fail function didn't fail");
    }
}

void test_fail_macro() {
    bool fail = false;
    try {
        FAIL();
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        throw testing::assertion_failure("FAIL macro didn't fail");
    }
}

void _throws() {
    throw std::runtime_error("Test error");
}

void _noop() {}

struct B {
    void method() {(void)this;}
};

void test_assert_throws() {
    testing::assert_throws<std::runtime_error>(_throws);
    
    bool fail = false;
    try {
        testing::assert_throws<std::length_error>(_noop);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("Assert throws didn't error on no-throw");
    }
}

void test_assert_throws_macro() {
    ASSERT_THROWS(std::runtime_error, _throws);
    
    bool fail = false;
    try {
        ASSERT_THROWS(std::length_error, _noop);
        fail = true;
    } catch (testing::assertion_failure&) {}
    
    if (fail) {
        testing::fail("ASSERT_THROWS didn't error on no-throw");
    }
}

void test_test_case() {
    auto __var2 = &_noop;
    testing::__TestCase<decltype(__var2)>* tc = new testing::__TestCase<decltype(__var2)>(__var2, "_noop");
    ASSERT(tc->get_name() == "_noop");
}

void run_test_tests() {
    TEST(test_assert)
    TEST(test_assert_macro)
    TEST(test_assert_equal)
    TEST(test_assert_equal_macro)
    TEST(test_assert_not_equal)
    TEST(test_assert_not_equal_macro)
    TEST(test_assert_files_equal)
    TEST(test_assert_files_not_equal)
    TEST(test_fail)
    TEST(test_fail_macro)
    TEST(test_assert_throws)
    TEST(test_assert_throws_macro)
    TEST(test_test_case)
}

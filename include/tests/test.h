#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include "types.h"
#include "utils/sfinae.h"
#include "tests/errors.h"
#include "tests/abstract_test.h"

/**
 * \file test.h
 * \brief Primary test running systems
 */

/**
 * Used inside a test class' run method, registers another method of the test class to be run as a test of its own.
 * If this is used, the run method will not count as a test, but all registered methods will.
 */
#define TEST_METHOD(name) { \
    this->delegated = true; \
    if (this->skip_test(#name)) { \
        testing::__test_on_skip(#name, testing::METHOD); \
    } else { \
        this->before_test(#name); \
        try { \
            this->name(); \
            testing::__test_on_success(#name, testing::METHOD); \
        } catch (testing::assertion_failure &e) { \
            testing::__test_on_failure(#name, e, testing::METHOD); \
        } catch (testing::skip_test &e) { \
            testing::__test_on_skip(#name, e, testing::METHOD); \
        } catch (std::exception &e) { \
            testing::__test_on_error(#name, e, testing::METHOD); \
        } \
        this->after_test(#name); \
    } \
}

/**
 * Registers a test class or function to be run as a test. Must be used for every class/function you wish to
 * run.
 *
 * Usage:
 *
 * ```
 * TEST(test_func)
 * TEST(TestClass())
 * ```
 */
#define TEST(NAME) { \
    auto __var1 = NAME; \
    testing::__TestPtr<decltype(__var1)>::type __var2 = testing::__TestPtr<decltype(__var1)>::make_ptr(__var1); \
    testing::__Config::test_cases.push_back(new testing::__TestCase<decltype(__var2)>(__var2, #NAME)); \
}

/**
 * Register a file to test. Expects a function of the name `run_[name]_tests` to exist in the namespace.
 */
#define TEST_FILE(NAME) testing::__Config::test_files.emplace_back(#NAME);run_##NAME##_tests();

namespace testing {

class TestCase;

enum TestType {
    FUNCTION, METHOD, CLASS
};

template<typename T, bool = std::is_pointer<T>::value>
struct __TestPtr {
    typedef T type;
    
    static T make_ptr(T val);
};

template<typename T>
struct __TestPtr<T, false> {
    typedef T* type;
    
    static T* make_ptr(T& val);
};

struct __Config {
	static std::vector<std::string> argv;
	static std::vector<std::string> test_files;
    static std::vector<TestCase*> test_cases;
};

struct __Results {
    static std::vector<std::string> failure_messages;
    static std::vector<std::string> skip_messages;
    static std::vector<std::string> error_messages;
};

struct Results {
    static int successes;
    static int failures;
    static int errors;
    static int skipped;
    
    static int total();
    static int success_percent();
    static int failure_percent();
    static int error_percent();
    static int skipped_percent();
};

std::string __get_name(TestType type);

void __test_on_success(const std::string& name, TestType type = FUNCTION);
void __test_on_failure(const std::string& name, assertion_failure& e, TestType type = FUNCTION);
void __test_on_skip(const std::string& name, TestType type = FUNCTION);
void __test_on_skip(const std::string& name, skip_test& e, TestType type = FUNCTION);
void __test_on_error(const std::string& name, std::exception& e, TestType type = FUNCTION);


/**
 * Prepare the test suite to run. Passed the arguments given to main,
 * for the command line arguments to run the tests with
 *
 * \param argc The number of command-line arguments
 * \param argv The string command line arguments
 */
void setup_tests(int argc, char const* const* argv);

/**
 * Run the test suite. Add any files to test with the macro `TEST_FILE(nameThe)` before running this.
 * Test files must define a function `run_[name]_tests()`.
 * In that function, use `TEST(name)` and `TEST_CLASS(name)` to define the function and test
 * classes to be run.
 *
 * \param name The name of the test suite being run. Customizes the output after tests are complete
 * \return Whether there were any failures, errors, or skips, as a bitfield.
 */
uint run_tests(const std::string& name = "Alpha Tools");

/**
 * Called after the test suite is complete, to ensure all memory is de-allocated. Not automatically
 * called in case the user wants to do their own results and test case handling. Fine to not call
 * if the program exits immediately after tests are run, but memory managers will warn about unfreed
 * memory all over the place.
 */
void teardown_tests();

}

#include "test.tpp"

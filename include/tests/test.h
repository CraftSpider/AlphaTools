#pragma once

#include <vector>
#include <type_traits>
#include "types.h"
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
#define TEST_METHOD(NAME) { \
    this->delegated = true; \
    if (this->skip_test(#NAME)) { \
        testing::__test_on_skip(#NAME, testing::TestType::METHOD); \
    } else { \
        this->before_test(#NAME); \
        try { \
            this->NAME(); \
            testing::__test_on_success(#NAME, testing::TestType::METHOD); \
        } catch (testing::assertion_failure& e) { \
            testing::__test_on_failure(#NAME, e, testing::TestType::METHOD); \
        } catch (testing::skip_test& e) { \
            testing::__test_on_skip(#NAME, e, testing::TestType::METHOD); \
        } catch (std::exception& e) { \
            testing::__test_on_error(#NAME, e, testing::TestType::METHOD); \
        } \
        this->after_test(#NAME); \
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

/**
 * Enum for what type a test is. Whether it's a Function, Method, or Class that's being tested.
 */
enum class TestType {
    FUNCTION, METHOD, CLASS
};

/**
 * \internal
 *
 * Special class, similar to util::MakePtr. However, when passed an instance, it actually returns a new instance, rather
 * than just referencing what was passed. Specialization for if the type is a pointer
 *
 * \tparam T Type to make into a pointer
 */
template<typename T, bool = std::is_pointer<T>::value>
struct __TestPtr {
    
    /**
     * Unchanged type, it's already a pointer
     */
    typedef T type;
    
    /**
     * Pass a pointer type through unchanged
     *
     * \param val Pointer to pass
     * \return Same as val
     */
    static T make_ptr(T val);
};

/**
 * Special class similar to util::MakePtr. Specialization for if the type is not a pointer
 *
 * \tparam T Type to make into a pointer
 */
template<typename T>
struct __TestPtr<T, false> {
    
    /**
     * Type with pointer added
     */
    typedef T* type;
    
    /**
     * Create a new instance of the referenced type and return it
     *
     * \param val Instance example
     * \return Pointer to new instance
     */
    static T* make_ptr(T& val);
};

/**
 * \internal
 *
 * Holds global testing configuration data, including all named files and the list of all tests to run
 */
struct __Config {
	static std::vector<std::string> argv;
	static std::vector<std::string> test_files;
    static std::vector<TestCase*> test_cases;
};

/**
 * \internal
 *
 * Private, internal result information. Stores the messages returned by all failed/skipped/errored tests
 */
struct __Results {
    static std::vector<std::string> failure_messages;
    static std::vector<std::string> skip_messages;
    static std::vector<std::string> error_messages;
};

/**
 * Public result information. Stores the number of successes/failures/errors/skips, and provides methods to get
 * statistical data about them.
 */
struct Results {
    static int successes;
    static int failures;
    static int errors;
    static int skipped;
    
    /**
     * Get the total number of tests run. Sum of successes, failures, errors, and skips
     *
     * \return Total test count
     */
    static int total();
    
    /**
     * Get the percentage of run tests that succeeded, truncated to nearest whole percent
     *
     * \return Percent of successful tests
     */
    static int success_percent();
    
    /**
     * Get the percentage of run tests that failed, truncated to nearest whole percent
     *
     * \return Percent of failed tests
     */
    static int failure_percent();
    
    /**
     * Get the percentage of run tests that errored, truncated to nearest whole percent
     *
     * \return Percent of errored tests
     */
    static int error_percent();
    
    /**
     * Get the percentage of run tests that were skipped, truncated to nearest whole percent
     * \return Percent of skipped tests
     */
    static int skipped_percent();
};

/**
 * \internal
 *
 * Get a TestType as a human-readable name for that value
 *
 * \param type TestType to get name of
 * \return Human-readable name
 */
std::string __get_name(TestType type);

/**
 * \internal
 *
 * Function called when a test succeeds. Passed the test and and type as context
 *
 * \param name Name of the test
 * \param type Type of the test
 */
void __test_on_success(const std::string& name, TestType type = TestType::FUNCTION);

/**
 * \internal
 *
 * Function called when a test fails. Passed the test name, type, and the assertion failure thrown
 * as context.
 *
 * \param name Name of the test
 * \param e assertion_failure that was thrown
 * \param type Type of the test
 */
void __test_on_failure(const std::string& name, assertion_failure& e, TestType type = TestType::FUNCTION);

/**
 * \internal
 *
 * Function called when a test is skipped without a skip_test throw. Passed the test name and type as context.
 *
 * \param name Name of the test
 * \param type Type of the test
 */
void __test_on_skip(const std::string& name, TestType type = TestType::FUNCTION);

/**
 * \internal
 *
 * Function called when a test is skipped due to a skip_test error. Passed the test name, type, and skip_test instance
 * as context.
 *
 * \param name Name of the test
 * \param e skip_test that was thrown
 * \param type Type of the test
 */
void __test_on_skip(const std::string& name, skip_test& e, TestType type = TestType::FUNCTION);

/**
 * \internal
 *
 * Function called when a test errors. Passed the name, type, and the exception thrown as context.
 *
 * \param name Name of the test
 * \param e exception that was thrown
 * \param type Type of the test
 */
void __test_on_error(const std::string& name, std::exception& e, TestType type = TestType::FUNCTION);


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

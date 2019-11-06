#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include "types.h"
#include "utils/sfinae.h"
#include "tests/abstract_test.h"

#define TEST_METHOD(name) {\
    this->delegated = true;\
    if (this->skip_test(#name)) {\
        testing::__test_on_skip(#name, testing::METHOD);\
    } else {\
        this->before_test(#name);\
        try {\
            this->name();\
            testing::__test_on_success(#name, testing::METHOD);\
        } catch (testing::assertion_failure &e) {\
            testing::__test_on_failure(#name, e, testing::METHOD);\
        } catch (testing::skip_test &e) {\
            testing::__test_on_skip(#name, e, testing::METHOD);\
        } catch (std::exception &e) {\
            testing::__test_on_error(#name, e, testing::METHOD);\
        }\
        this->after_test(#name);\
    }\
}

#define TEST(name) {\
    auto __val1 = name;\
    util::MakePtr<decltype(__val1)>::type __var = util::MakePtr<decltype(__val1)>::make_ptr(__val1);\
    testing::__TestCase<decltype(__var)>(__var, #name).run();\
}

#define TEST_FILE(name) testing::__Config::tests.push_back(&run_##name##_tests);

namespace testing {

struct __Config {
	static std::vector<std::string> argv;
    static std::vector<void (*)()> tests;
};

struct __Results {
    static std::vector<std::string> failure_messages;
    static std::vector<std::string> skip_messages;
    static std::vector<std::string> error_messages;
};

enum TestType {
    FUNCTION, METHOD, CLASS
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

class test_error : public std::runtime_error {
protected:
    explicit test_error(const std::string& msg);
};

class assertion_failure : public test_error {
public:
    explicit assertion_failure(const std::string& msg);
};

class skip_test : public test_error {
public:
    skip_test();
    explicit skip_test(const std::string& msg);
};

std::string __get_name(TestType type);

void __test_on_success(const std::string& name, TestType type = FUNCTION);
void __test_on_failure(const std::string& name, assertion_failure& e, TestType type = FUNCTION);
void __test_on_skip(const std::string& name, TestType type = FUNCTION);
void __test_on_skip(const std::string& name, skip_test& e, TestType type = FUNCTION);
void __test_on_error(const std::string& name, std::exception& e, TestType type = FUNCTION);

template<typename T>
class __TestCase {
    
    T instance;
    std::string name;
    
public:
    
    __TestCase(T inst, const std::string& name) {
        this->instance = inst;
        this->name = name;
    }
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int> = 0>
    void __run() {
        try {
            (*this->instance)();
            testing::__test_on_success(name);
        } catch (testing::assertion_failure &e) {
            testing::__test_on_failure(name, e);
        } catch (testing::skip_test &e) {
            testing::__test_on_skip(name, e);
        } catch (std::exception &e) {
            testing::__test_on_error(name, e);
        }
    }
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::pointer, int> = 0>
    void __run() {
        if (instance->skip_class()) {
            testing::__test_on_skip(name, testing::CLASS);
        } else {
            instance->before_class();
            try {
                instance->run();
                if (!instance->delegated) {
                    testing::__test_on_success(name, testing::CLASS);
                }
            } catch (testing::assertion_failure &e) {
                if (!instance->delegated) {
                    testing::__test_on_failure(name, e, testing::CLASS);
                }
            } catch (testing::skip_test &e) {
                testing::__test_on_skip(name, e, testing::CLASS);
            } catch (std::exception &e) {
                if (!instance->delegated) {
                    testing::__test_on_error(name, e, testing::CLASS);
                }
            }
            instance->after_class();
        }
    }
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::method, int> = 0>
    void __run() {}
    
    template<typename C, typename K, std::enable_if_t<!util::TypeFinder<C>::method, int> = 0>
    void __run(K* self) {}
    
    template<typename C, typename K, std::enable_if_t<util::TypeFinder<C>::method, int> = 0>
    void __run(K* self) {
        self->delegated = true;
        if (self->skip_test(name)) {
            testing::__test_on_skip(name, testing::METHOD);
        } else {
            self->before_test(name);
            try {
                (self->*instance)();
                testing::__test_on_success(name, testing::METHOD);
            } catch (testing::assertion_failure &e) {
                testing::__test_on_failure(name, e, testing::METHOD);
            } catch (testing::skip_test &e) {
                testing::__test_on_skip(name, e, testing::METHOD);
            } catch (std::exception &e) {
                testing::__test_on_error(name, e, testing::METHOD);
            }
            self->after_test(name);
        }
    }
    
    void run() {
        __run<T>();
    }
    
    template<typename K>
    void run(K* self) {
        __run<T, K>(self);
    }
    
};


/**
 * Prepare the test suite to run. Passed the arguments given to main,
 * for the command line arguments to run the tests with
 */
void setup_tests(int argc, char const* const* argv);

/**
 * Run the test suite. Add any files to test with the macro `TEST_FILE(nameThe)` before running this.
 * Test files must define a function `run_[name]_tests()`.
 * In that function, use `TEST(name)` and `TEST_CLASS(name)` to define the function and test
 * classes to be run.
 */
uint run_tests(const std::string& name = "Alpha Tools");

}

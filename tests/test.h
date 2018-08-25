#pragma once

#include <vector>
#include <iostream>
#include "types.h"

#define ASSERT(expr) if (!(expr)) {throw assertion_failure(std::string("Expression \"") + #expr + "\" failed assertion");}

#define TEST(name) try {\
    name();\
    Results::successes += 1;\
} catch (assertion_failure &e) {\
    std::cerr << e.what() << " in test " << #name << std::endl;\
    Results::failures += 1;\
} catch (std::exception &e) {\
    std::cerr << e.what() << " in test " << #name << std::endl;\
    Results::errors += 1;\
}

#define TEST_CLASS(name) AbstractTest *test##name = new name();\
if (test##name->skip_test()) {\
    std::cout << "Skipped test class " << #name;\
    Results::skipped += 1;\
} else {\
    test##name->before_test();\
    try {\
        test##name->run();\
        Results::successes += 1;\
    } catch (assertion_failure &e) {\
        std::cerr << e.what() << " in test class " << #name << std::endl;\
        Results::failures += 1;\
    } catch (std::exception &e) {\
        std::cerr << e.what() << " in test class " << #name << std::endl;\
        Results::errors += 1;\
    }\
    test##name->after_test();\
}\
delete test##name;

#define TEST_FILE(name) run_##name##_tests();

struct Results {
    static int successes;
    static int failures;
    static int errors;
    static int skipped;
};

class assertion_failure : public std::runtime_error {
public:
    explicit assertion_failure(const std::string& msg);
};

class AbstractTest {

public:
    
    virtual ~AbstractTest();
    
    virtual bool skip_test();
    virtual void before_test();
    virtual void run() = 0;
    virtual void after_test();
    
};

/**
 * Run the test suite. Add any new test files here with the macro `TEST_FILE(filename)`.
 * Test files must define a function `run_[name]_tests()`.
 * In that function, use `TEST(name)` and `TEST_CLASS(name)` to define the function and test
 * classes to be run.
 */
void run_tests();

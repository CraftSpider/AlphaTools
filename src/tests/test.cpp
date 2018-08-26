
#include "test.h"

namespace testing {

std::vector<void (*)()> Results::tests = std::vector<void (*)()>();
int Results::successes = 0;
int Results::failures = 0;
int Results::errors = 0;
int Results::skipped = 0;

assertion_failure::assertion_failure(const std::string &msg) : runtime_error(msg) {}

AbstractTest::~AbstractTest() {}

bool AbstractTest::skip_test() {
    return false;
}

void AbstractTest::before_class() {}

void AbstractTest::before_test(std::string name) {}

void AbstractTest::after_test(std::string name) {}

void AbstractTest::after_class() {}

void run_tests(std::string name) {
    for (auto test : Results::tests) {
        test();
    }
    
    std::cout << name << " testing complete. Results:\n";
    std::cout << "Successes: " << Results::successes << " Failures: " << Results::failures;
    std::cout << " Errors: " << Results::errors << " Skipped: " << Results::skipped << "\n";
}

}


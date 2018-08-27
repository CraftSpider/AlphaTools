
#include <console.h>
#include "tests/test.h"
#include "console.h"

namespace testing {

std::vector<void(*)()> ToRun::tests = std::vector<void (*)()>();

int Results::successes = 0;
int Results::failures = 0;
int Results::errors = 0;
int Results::skipped = 0;

int Results::total() {
    return successes + failures + errors + skipped;
}

assertion_failure::assertion_failure(const std::string &msg) : runtime_error(msg) {};

skip_test::skip_test() : runtime_error("Skipped test") {};
skip_test::skip_test(const std::string &msg) : runtime_error(msg) {};

constexpr char fill_char = '=';
constexpr char blank_char = '-';

void run_tests(std::string name) {
    for (auto test : ToRun::tests) {
        test();
    }
    
    std::cout << name << " testing complete. Results:\n";
    std::cout << "Tests Found: " << Results::total() << "\n";
    std::cout << "Successes: " << term::fore::GREEN << Results::successes << term::fore::DEFAULT;
    std::cout << " Failures: " << term::fore::RED << Results::failures << term::fore::DEFAULT;
    std::cout << " Errors: " << term::fore::YELLOW << Results::errors << term::fore::DEFAULT;
    std::cout << " Skipped: " << term::fore::LIGHT_BLUE << Results::skipped << term::fore::DEFAULT << "\n";

    int percent = 100 * Results::successes / Results::total();
    std::cout << "[";
    for (int i = 0; i < 25; ++i) {
        if (i*2 < percent)
            std::cout << fill_char;
        else
            std::cout << blank_char;
    }
    std::cout << percent << "%";
    for (int i = 25; i < 50; ++i) {
        if (i*2 < percent)
            std::cout << fill_char;
        else
            std::cout << blank_char;
    }
    std::cout << "]\n";
}

}



#include <chrono>
#include <typeinfo>
#include "tests/test.h"
#include "tests/test_case.h"
#include "console.h"

#if defined(__CYGWIN__)
#warning Most console codes will not work on windows terminals before Win10
#endif

namespace testing {

std::vector<std::string> __Config::argv = std::vector<std::string>();
std::vector<std::string> __Config::test_files = std::vector<std::string>();
std::vector<TestCase*> __Config::test_cases = std::vector<TestCase*>();

std::vector<std::string> __Results::failure_messages = std::vector<std::string>();
std::vector<std::string> __Results::skip_messages = std::vector<std::string>();
std::vector<std::string> __Results::error_messages = std::vector<std::string>();

int Results::successes = 0;
int Results::failures = 0;
int Results::errors = 0;
int Results::skipped = 0;

int Results::total() {
    return successes + failures + errors + skipped;
}

int Results::success_percent() {
    return 100 * successes / total();
}

int Results::failure_percent() {
    return 100 * failures / total();
}

int Results::error_percent() {
    return 100 * errors / total();
}

int Results::skipped_percent() {
    return 100 * skipped / total();
}

constexpr char fill_char = '=';
constexpr char blank_char = '-';

std::string __get_name(TestType type) {
    switch (type) {
        case FUNCTION:
            return "test";
        case METHOD:
            return "test method";
        case CLASS:
            return "test class";
    }
    return "unknown";
}

void __test_on_success(const std::string&, TestType) {
    Results::successes += 1;
}

void __test_on_failure(const std::string& name, assertion_failure& e, TestType type) {
    std::stringstream stream;
    stream << e.what() << " in " << __get_name(type) << " " << name;
    __Results::failure_messages.push_back(stream.str());
    
    Results::failures += 1;
}

void __test_on_skip(const std::string& name, TestType type) {
    std::stringstream stream;
    stream << "Skipped " << __get_name(type) << " " << name;
    __Results::skip_messages.push_back(stream.str());
    
    Results::skipped += 1;
}

void __test_on_skip(const std::string& name, skip_test& e, TestType type) {
    std::stringstream stream;
    if (e.what() == std::string("Skipped test")) {
        stream << "Skipped " << __get_name(type) << " " << name;
    } else {
        stream << "Skipped " << __get_name(type) << " " << name << " with message " << e.what();
    }
    __Results::skip_messages.push_back(stream.str());
    
    Results::skipped += 1;
}

void __test_on_error(const std::string& name, std::exception& e, TestType type) {
    std::stringstream stream;
    std::string type_name = typeid(e).name();
    stream << type_name << ": " << e.what() << " in " << __get_name(type) << " " << name;
    __Results::error_messages.push_back(stream.str());
    
    Results::errors += 1;
}

void setup_tests(int argc, char const* const* argv) {
	for (int i = 0; i < argc; ++i) {
		__Config::argv.emplace_back(std::string(argv[i]));
	}
}

uint run_tests(const std::string& name) {
    using namespace std::chrono;
    using namespace term;
    
    time_point start = high_resolution_clock::now();
    for (auto test : __Config::test_cases) {
        test->run();
    }
    
    time_point end = high_resolution_clock::now();
    duration elapsed = end - start;
    
    // Write out basic results
    std::cout << term::RESET_ALL;
    std::cout << "\n" << name << " testing complete. Results:\n";
    std::cout << "Ran " << Results::total() << " tests in " << (float)elapsed.count() / nanoseconds(seconds(1)).count() << " seconds\n";
    std::cout << "Successes: " << fore::GREEN << Results::successes << fore::DEFAULT;
    std::cout << " Failures: " << fore::RED << Results::failures << fore::DEFAULT;
    std::cout << " Skipped: " << fore::LIGHT_BLUE << Results::skipped << fore::DEFAULT;
    std::cout << " Errors: " << fore::YELLOW << Results::errors << fore::DEFAULT << "\n";
    
    // Write out percentage bar
    std::cout << "[" << fore::GREEN;
    for (int i = 0; i < Results::success_percent() / 2; ++i) {
        std::cout << fill_char;
    }
    std::cout << fore::RED;
    for (int i = 0; i < Results::failure_percent() / 2; ++i) {
        std::cout << fill_char;
    }
    std::cout << fore::LIGHT_BLUE;
    for (int i = 0; i < Results::skipped_percent() / 2; ++i) {
        std::cout << blank_char;
    }
    std::cout << fore::YELLOW;
    for (int i = 0; i < Results::error_percent() / 2; ++i) {
        std::cout << blank_char;
    }
    std::cout << fore::DEFAULT << "]\n\n";
    
    // Write out messages
    if (!__Results::failure_messages.empty()) {
        std::cout << fore::RED << effect::UNDERLINE << "Failure messages:\n" << effect::RESET_UNDERLINE << fore::DEFAULT;
        for (const std::string& i : __Results::failure_messages) {
            std::cout << i << "\n";
        }
        std::cout << "\n";
    }
    if (!__Results::skip_messages.empty()) {
        std::cout << fore::LIGHT_BLUE << effect::UNDERLINE << "Skip messages:\n" << effect::RESET_UNDERLINE << fore::DEFAULT;
        for (const std::string& i : __Results::skip_messages) {
            std::cout << i << "\n";
        }
        std::cout << "\n";
    }
    if (!__Results::error_messages.empty()) {
        std::cout << fore::YELLOW << effect::UNDERLINE << "Error messages:\n" << effect::RESET_UNDERLINE << fore::DEFAULT;
        for (const std::string& i : __Results::error_messages) {
            std::cout << i << "\n";
        }
        std::cout << "\n";
    }
    
    std::cout << std::flush;
    
    // Return bitmask based on test results
    int out = 0;
    if (Results::failures) {
        out += 0b001;
    }
    if (Results::errors) {
        out += 0b010;
    }
    if (Results::skipped) {
        out += 0b100;
    }
    return out;
}

}


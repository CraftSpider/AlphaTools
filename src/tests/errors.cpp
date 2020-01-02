
#include "tests/errors.h"

namespace testing {

constexpr const char* skip_def_msg = "Skipped test";

test_exception::test_exception(const std::string &msg) {
    message = msg;
}

const char* test_exception::what() const noexcept {
    return message.c_str();
}

assertion_failure::assertion_failure(const std::string &msg) : test_exception(msg) {}

skip_test::skip_test() : test_exception(skip_def_msg) {}
skip_test::skip_test(const std::string &msg) : test_exception(msg) {}

}

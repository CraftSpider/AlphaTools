
#include "tests/errors.h"

namespace testing {

static std::string skip_def_msg = "Skipped test";

test_error::test_error(const std::string &msg) : runtime_error(msg) {}

assertion_failure::assertion_failure(const std::string &msg) : test_error(msg) {}

skip_test::skip_test() : test_error(skip_def_msg) {}
skip_test::skip_test(const std::string &msg) : test_error(msg) {}

}

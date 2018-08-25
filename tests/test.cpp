
#include "test.h"

#include "test_bytes.h"
#include "test_arrays.h"

int Results::successes = 0;
int Results::failures = 0;
int Results::errors = 0;
int Results::skipped = 0;

assertion_failure::assertion_failure(const std::string &msg) : runtime_error(msg) {}

AbstractTest::~AbstractTest() {}

bool AbstractTest::skip_test() {
    return false;
}

void AbstractTest::before_test() {}

void AbstractTest::after_test() {}

void run_tests() {
    TEST_FILE(bytes)
    TEST_FILE(arrays)
}


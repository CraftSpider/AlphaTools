
#include "at_tests"

#include "test_algorithms.h"
#include "test_arrays.h"
#include "test_bytes.h"
#include "test_strmanip.h"
#include "test_logging.h"

int main(int argc, char **argv) {
    TEST_FILE(algorithms)
    TEST_FILE(arrays)
    TEST_FILE(bytes)
    TEST_FILE(strmanip)
    TEST_FILE(logging)
    
    testing::run_tests();
}
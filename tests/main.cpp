
#include "../include/tests/test.h"

#include "test_bytes.h"
#include "test_arrays.h"

int main(int argc, char **argv) {
    TEST_FILE(bytes)
    TEST_FILE(arrays)
    
    testing::run_tests();
}
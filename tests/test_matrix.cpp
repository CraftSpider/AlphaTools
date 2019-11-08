
#include <math/matrix.h>
#include "at_tests"
#include "test_matrix.h"

void test_construct() {
    math::Matrix m = math::Matrix(1, 1);
    
    std::cout << m[0][0] << "\n";
}

void run_matrix_tests() {
    TEST(test_construct)
}

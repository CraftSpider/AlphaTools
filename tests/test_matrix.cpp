
#include <math/matrix.h>
#include "at_tests"
#include "test_matrix.h"

void test_construct() {
    math::Matrix m = math::Matrix(1, 1);
    
    ASSERT(m.rows == 1 && m.columns == 1);
    ASSERT(m[0].length == 1);
    ASSERT(m[0][0] == 0);
    
    double args[2][2] = {{1., 2.}, {3., 4.}};
    
    math::Matrix m1 = math::Matrix(2, 2, (double*)args);
    
    ASSERT(m1[0][0] == 1.);
    ASSERT(m1[0][1] == 2.);
    ASSERT(m1[1][0] == 3.);
    ASSERT(m1[1][1] == 4.);
    
    double args2[2][3] = {{1, 2, -1}, {2, 0, 1}};
    math::Matrix m2 = math::Matrix(2, 3, (double*)args2);
    
    ASSERT(m2[0][0] == 1);
    ASSERT(m2[0][1] == 2);
    ASSERT(m2[0][2] == -1);
    ASSERT(m2[1][0] == 2);
    ASSERT(m2[1][1] == 0);
    ASSERT(m2[1][2] == 1);
}

void invalid_add(math::Matrix<double>& a, math::Matrix<double>& b) {
    a + b;
}

void invalid_mult(math::Matrix<double>& a, math::Matrix<double>& b) {
    a * b;
}

void test_addition() {
    double args[2][2] = {{1, 2}, {3, 4}};
    double args2[2][2] = {{2, -1}, {5, 0}};
    math::Matrix m1 = math::Matrix(2, 2, (double*)args);
    math::Matrix m2 = math::Matrix(2, 2, (double*)args2);
    math::Matrix m3 = math::Matrix(1, 2);
    
    math::Matrix result = m1 + m2;
    math::Matrix result2 = m2 + m1;
    
    ASSERT(result.rows == m1.rows && result.columns == m1.columns);
    ASSERT(result[0][0] == 3);
    ASSERT(result[0][1] == 1);
    ASSERT(result[1][0] == 8);
    ASSERT(result[1][1] == 4);
    ASSERT(result == result2);
    
    testing::assert_throws<std::invalid_argument>(&invalid_add, m1, m3);
    
}

void test_multiply() {
    double args[2][3] = {{1, 2, -1}, {2, 0, 1}};
    double args2[3][2] = {{3, 1}, {0, -1}, {-2, 3}};
    math::Matrix m1 = math::Matrix(2, 3, (double*)args);
    math::Matrix m2 = math::Matrix(3, 2, (double*)args2);
    math::Matrix m3 = math::Matrix(2, 2);
    
    math::Matrix result = m1 * m2;
    
    ASSERT(result.rows == 2 && result.columns == 2);
    ASSERT(result[0][0] == 5);
    ASSERT(result[0][1] == -4);
    ASSERT(result[1][0] == 4);
    ASSERT(result[1][1] == 5);
    
    testing::assert_throws<std::invalid_argument>(&invalid_mult, m1, m3);
}

void run_matrix_tests() {
    TEST(test_construct)
    TEST(test_addition)
    TEST(test_multiply)
}

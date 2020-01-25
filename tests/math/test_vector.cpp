
#include "at_tests"
#include "at_math"

using namespace math;

static void test_construct() {
    Vector a = Vector();
    ASSERT(a.x == 0 && a.y == 0 && a.z == 0);
    
    a = Vector(5.);
    
    ASSERT(a.x == 5. && a.y == 5. && a.z == 5.);
    
    a = Vector(1., 2., 3.);
    
    ASSERT(a.x == 1. && a.y == 2. && a.z == 3.);
}

void test_compare() {
    Vector a = Vector(1);
    Vector b = Vector(2);
    Vector c = Vector(1);
    
    ASSERT(a == c);
    
    ASSERT(a != b);
}

void test_add() {
    Vector a = Vector(1);
    Vector b = Vector(-2, 0, 2);
    
    ASSERT(a + b == Vector(-1, 1, 3));
    ASSERT(a + b == b + a);
    
    ASSERT(a + Vector::zero_vec == a);
    
    ASSERT(a + 1 == Vector(2));
    ASSERT(b + 2 == Vector(0, 2, 4));
    
    Vector c = Vector(3, 4, 5);
    
    c += a;
    ASSERT(c == Vector(4, 5, 6));
}

void test_subtract() {
    Vector a = Vector(1);
    Vector b = Vector(-2, 0, 2);
    
    ASSERT(a - b == Vector(3, 1, -1));
    ASSERT(a - b != b - a);
    
    ASSERT(a - Vector::zero_vec == a);
    ASSERT(a - Vector::one_vec == Vector::zero_vec);
    
    ASSERT(a - 1 == Vector(0));
    ASSERT(b - 2 == Vector(-4, -2, 0));
    
    Vector c = Vector(3, 4, 5);
    
    c -= a;
    ASSERT(c == Vector(2, 3, 4));
}

void test_mult() {
    Vector a = Vector(2);
    Vector b = Vector(0, .5, 3);
    
    ASSERT(a * b == Vector(0, 1, 6));
    ASSERT(a * b == b * a);
    
    ASSERT(a * Vector::zero_vec == Vector::zero_vec);
    ASSERT(a * Vector::one_vec == a);
    
    ASSERT(b * 3 == Vector(0, 1.5, 9));
    ASSERT(a * 1 == a);
    
    Vector c = Vector(1, 5, 10);
    
    c *= b;
    ASSERT(c == Vector(0, 2.5, 30));
}

void test_divide() {
    Vector a = Vector(2);
    Vector b = Vector(2, 4, 3);
    
    ASSERT(a / b == Vector(1, .5, 2./3.));
    ASSERT(a / b != b / a);
    
    ASSERT(Vector::zero_vec / a == Vector::zero_vec);
    ASSERT(a / Vector::one_vec == a);
    
    ASSERT(a / 2 == Vector(1));
    ASSERT(b / 4 == Vector(.5, 1, 3./4.));
    
    Vector c = Vector(10);
    
    c /= b;
    ASSERT(c == Vector(5, 2.5, 10./3.));
}

void test_dot() {
    throw testing::skip_test();
}

void test_cross() {
    ASSERT((Vector::x_axis ^ Vector::y_axis) == Vector::z_axis);
    ASSERT((Vector::y_axis ^ Vector::x_axis) == -Vector::z_axis);
    
    ASSERT((Vector::y_axis ^ Vector::z_axis) == Vector::x_axis);
    ASSERT((Vector::z_axis ^ Vector::y_axis) == -Vector::x_axis);
    
    ASSERT((Vector::z_axis ^ Vector::x_axis) == Vector::y_axis);
    ASSERT((Vector::x_axis ^ Vector::z_axis) == -Vector::y_axis);
    
    ASSERT(Vector::x_axis.cross(Vector::y_axis) == (Vector::x_axis ^ Vector::y_axis));
}

void test_dist() {
    Vector a = Vector(1, 0, 0);
    Vector b = Vector(-1, 0, 0);
    Vector c = Vector(0, 1, 0);
    
    ASSERT(a.distance(b) == 2);
    ASSERT(a.distance(b) == b.distance(a));
    ASSERT(a.distance(b) == Vector::distance(a, b));
    
    ASSERT(a.distance(c) == b.distance(c));
    
    ASSERT(a.distance_sq(b) == 4);
    ASSERT(a.distance_sq(b) == b.distance_sq(a));
    ASSERT(a.distance_sq(b) == Vector::distance_sq(a, b));
    
    ASSERT(a.distance_sq(c) == b.distance_sq(c));
}

void test_normal() {
    throw testing::skip_test();
}

void run_vector_tests() {
    TEST(test_construct)
    TEST(test_compare)
    TEST(test_add)
    TEST(test_subtract)
    TEST(test_mult)
    TEST(test_divide)
    TEST(test_dot)
    TEST(test_cross)
    TEST(test_dist)
    TEST(test_normal)
}


#include <at_tests>
#include <at_math>

#include "test_sphere.h"

using namespace math;

static void test_construct() {
    Sphere s = Sphere();
    
    ASSERT(s.center == Vector::zero_vec);
    ASSERT(s.radius == 0);
    
    Sphere s1 = Sphere(Vector(1, 2, 3), 5);
    
    ASSERT(s1.center == Vector(1, 2, 3));
    ASSERT(s1.radius == 5);
}

static void test_compare() {
    Sphere s1 = Sphere(Vector::x_axis, 2.5);
    Sphere s2 = Sphere(Vector::x_axis, 2.5);
    Sphere s3 = Sphere(Vector::y_axis, 2.5);
    Sphere s4 = Sphere(Vector::x_axis, 5);
    
    ASSERT(s1 == s2);
    ASSERT(s1 != s3);
    ASSERT(s1 != s4);
}

void run_sphere_tests() {
    TEST(test_construct)
    TEST(test_compare)
}


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

void run_vector_tests() {
    TEST(test_construct)
    TEST(test_compare)
}

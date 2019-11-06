
#include "at_tests"
#include "utils/sfinae.h"
#include "test_sfinae.h"

void test_makeptr() {
    typedef util::MakePtr<int>::type Type1;
    typedef util::MakePtr<int*>::type Type2;

    int a = 1;

    ASSERT(typeid(Type1) == typeid(Type2));
    ASSERT(util::MakePtr<int>::make_ptr(a) == &a);
    ASSERT(util::MakePtr<int*>::make_ptr(&a) == &a);
}

void run_sfinae_tests() {
    TEST(test_makeptr)
}

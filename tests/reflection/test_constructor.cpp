
#include <at_tests>
#include "test_constructor.h"
#include "at_reflect"

struct A {
    int a = 0;
    
    A() = default;
    
    A(int b) {
        a = b;
    }
    
};

DECLARE_TYPE(A)

void make_too_few() {
    reflect::Constructor c2 = reflect::Constructor::from<A, int>();
    c2.construct(std::vector<reflect::Variant>());
}

void make_too_many() {
    reflect::Constructor c2 = reflect::Constructor::from<A, int>();
    c2.construct(
        std::vector<reflect::Variant> {reflect::Variant::from_instance(2), reflect::Variant::from_instance(3)}
    );
}

void make_wrong_type() {
    reflect::Constructor c2 = reflect::Constructor::from<A, int>();
    c2.construct(
            std::vector<reflect::Variant> {reflect::Variant::from_instance(2.f)}
    );
}

void test_num_args() {
    reflect::Constructor c1 = reflect::Constructor::from<A>();
    reflect::Constructor c2 = reflect::Constructor::from<A, int>();
    
    ASSERT(c1.get_num_args() == 0);
    ASSERT(c2.get_num_args() == 1);
}

void test_construct_correct() {
    reflect::Constructor c1 = reflect::Constructor::from<A>();
    reflect::Constructor c2 = reflect::Constructor::from<A, int>();
    
    A* a1 = c1.construct(std::vector<reflect::Variant>()).get_value_ptr<A>();
    A* a2 = c2.construct(
            std::vector<reflect::Variant> {reflect::Variant::from_instance(2)}
    ).get_value_ptr<A>();
    
    ASSERT(a1->a == 0);
    ASSERT(a2->a == 2);
}

void test_bad_inputs() {
    testing::assert_throws<reflect::invalid_size>(
        &make_too_few
    );
    
    testing::assert_throws<reflect::invalid_size>(
        &make_too_many
    );
    
    testing::assert_throws<reflect::invalid_type>(
        &make_wrong_type
    );
}

void run_constructor_tests() {
    TEST(test_num_args)
    TEST(test_construct_correct)
    TEST(test_bad_inputs)
}

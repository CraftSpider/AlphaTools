
#include "at_tests"
#include "at_reflect"


using namespace reflect;


struct A {
    int a = 0;
    
    A() = default;
    
    explicit A(int b) {
        a = b;
    }
    
};

DECLARE_TYPE(A)

void make_too_few() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct({});
}

void make_too_many() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct(
        {Variant::from_instance(2), Variant::from_instance(3)}
    );
}

void make_wrong_type() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct(
            std::vector<Variant> {Variant::from_instance(2.f)}
    );
}

void make_invalid_noarg() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct();
}

void make_too_many_unsafe() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct_unsafe(
        {Variant::from_instance(2), Variant::from_instance(3)}
    );
}

void make_wrong_type_unsafe() {
    Constructor& c2 = Constructor::from<A, int>();
    c2.construct_unsafe(
        std::vector<Variant> {Variant::from_instance(2.f)}
    );
}

void test_construct_correct() {
    Constructor& c1 = Constructor::from<A>();
    Constructor& c2 = Constructor::from<A, int>();
    
    A* a1 = c1.construct({}).take_value_ptr<A>();
    A* a2 = c2.construct(
            {Variant::from_instance(2)}
    ).take_value_ptr<A>();
    
    ASSERT(a1->a == 0);
    ASSERT(a2->a == 2);
    
    delete a1;
    delete a2;
}

void test_construct_noarg() {
    Constructor& c1 = Constructor::from<A>();
    
    A* a = c1.construct().take_value_ptr<A>();
    
    ASSERT(a->a == 0);
    
    delete a;
}

void test_construct_unsafe() {
    Constructor& c1 = Constructor::from<A>();
    Constructor& c2 = Constructor::from<A, int>();
    
    A* a1 = (A*)c1.construct_unsafe({});
    A* a2 = (A*)c2.construct_unsafe(
        {Variant::from_instance(2)}
    );
    
    ASSERT(a1->a == 0);
    ASSERT(a2->a == 2);
    
    delete a1;
    delete a2;
}

void test_bad_inputs() {
    testing::assert_throws<invalid_size>(
        &make_too_few
    );
    
    testing::assert_throws<invalid_size>(
        &make_too_many
    );
    
    testing::assert_throws<invalid_type>(
        &make_wrong_type
    );
    
    testing::assert_throws<invalid_size>(
        &make_invalid_noarg
    );
    
    testing::assert_throws<invalid_size>(
        &make_too_many_unsafe
    );
    
    testing::assert_throws<invalid_type>(
        &make_wrong_type_unsafe
    );
}

static void test_type_links() {
    Constructor& c1 = Constructor::from<A>();
    Constructor& c2 = Constructor::from<A, int>();
    
    ASSERT(c1.get_type() == Type::from<A>());
    ASSERT(c2.get_type() == Type::from<A>());
    
    ASSERT(c1.get_arg_types().empty());
    ASSERT(c2.get_arg_types() == std::vector<Type*> {Type::from<int>()});
}

void test_num_args() {
    Constructor& c1 = Constructor::from<A>();
    Constructor& c2 = Constructor::from<A, int>();
    
    ASSERT(c1.get_num_args() == 0);
    ASSERT(c2.get_num_args() == 1);
}

void run_constructor_tests() {
    TEST(test_construct_correct)
    TEST(test_construct_noarg)
    TEST(test_construct_unsafe)
    TEST(test_bad_inputs)
    TEST(test_type_links)
    TEST(test_num_args)
}

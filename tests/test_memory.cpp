
#include "at_tests"
#include "utils/memory.h"

class TestMove {
    int a;
public:
    float b;
    TestMove(int a, float b) {
        this->a = a;
        this->b = b;
    };
    
    TestMove(TestMove&) = delete;
    TestMove(TestMove&&) = delete;
    
    int get_a() {return a;}
};

static void test_copy() {
    TestMove test = TestMove(-5, -1.f);
    
    TestMove* result = util::raw_copy(test);
    
    ASSERT(test.get_a() == -5);
    ASSERT(test.b == -1.f);
    ASSERT(result->get_a() == -5);
    ASSERT(result->b == -1.f);
    
    delete result;
}

static void test_raw_move() {
    TestMove test = TestMove(10, .5);
    
    TestMove* result = util::raw_move(test);
    
    ASSERT(test.get_a() == 0);
    ASSERT(test.b == 0);
    ASSERT(result->get_a() == 10);
    ASSERT(result->b == .5);
    
    delete result;
    
    TestMove src = TestMove(-10, 1.2f);
    TestMove dst = TestMove(5, 3.3f);
    
    util::raw_move(src, dst);
    
    ASSERT(src.get_a() == 0);
    ASSERT(src.b == 0);
    ASSERT(dst.get_a() == -10);
    ASSERT(dst.b == 1.2f);
}

void run_memory_tests() {
    TEST(test_copy)
    TEST(test_raw_move)
}

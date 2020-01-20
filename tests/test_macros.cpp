
#include "at_macros"
#include "at_tests"

#define TEST_A 1
#define TEST_B TEST_A
#define TEST_C 2
#define TEST_CALL(NAME) AT_##NAME

#define TEST_VARIADIC_3(...) AT_EXPAND(AT_VARIADIC_THREE(__VA_ARGS__, "C", "B", "A", "INVALID"))

void test_stringify() {
    ASSERT(AT_STRINGIFY(TEST_B) == std::string("1"));
    ASSERT(AT_STRINGIFY(TEST_C) == std::string("2"));
    ASSERT(AT_STRINGIFY(TEST_CALL(NEW_NAME)) == std::string("AT_NEW_NAME"));
}

void test_variadic() {
    std::string arg1 = TEST_VARIADIC_3(A);
    
    AT_ASSERT(arg1 == "A");
    
    std::string arg2 = TEST_VARIADIC_3(A, B);
    
    ASSERT(arg2 == "B");
    
    std::string arg3 = TEST_VARIADIC_3(A, B, C);
    
    ASSERT(arg3 == "C");
}

void run_macro_tests() {
    TEST(test_stringify)
    TEST(test_variadic)
}

#undef TEST_A
#undef TEST_B
#undef TEST_C
#undef TEST_CALL
#undef TEST_VARIADIC_3

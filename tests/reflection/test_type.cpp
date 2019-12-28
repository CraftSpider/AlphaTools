
#include "test_type.h"
#include "at_tests"
#include "at_reflect"

using namespace reflect;

void test_type_from() {
    Type* type1 = Type::from<int>();
    int temp = 1;
    Type* type2 = Type::from_instance(&temp);
    Type* type3 = Type::from_name("int");
    
    ASSERT(type1 == type2, "from<int> didn't match from_instance<int>");
    ASSERT(type1 == type3, "from<int> didn't match from_name(\"int\")");
}

void test_type_name() {
    Type* type1 = Type::from<int>();
    Type* type2 = Type::from<Type>();
    
    ASSERT(type1->get_name() == "int");
    ASSERT(type2->get_name() == "reflect::Type");
}

void run_type_tests() {
    TEST(test_type_from)
    TEST(test_type_name)
}

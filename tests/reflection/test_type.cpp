
#include "test_type.h"
#include "at_tests"
#include "at_reflect"

using namespace reflect;

class ReflectedType {};
class UnreflectedType {};

DECLARE_TYPE(int*)
DECLARE_TYPE(ReflectedType)

void test_type_from() {
    Type* type1 = Type::from<int>();
    int temp = 1;
    Type* type2 = Type::from_instance(&temp);
    Type* type3 = Type::from_name("int");
    
    ASSERT(type1 == type2, "from<int> didn't match from_instance<int>");
    ASSERT(type1 == type3, "from<int> didn't match from_name(\"int\")");
    
    ReflectedType temp2 = {};
    Type* type4 = Type::from_instance(&temp2);
    Type* type5 = Type::from<ReflectedType>();
    Type* type6 = Type::from_name("ReflectedType");
    
    ASSERT(type4 == type5, "from_instance<ReflectedType> didn't match from<ReflectedType>");
    ASSERT(type4 == type6, "from_instance<ReflectedType> didn't match from_name(\"ReflectedType\")");
}

void test_type_name() {
    Type* type1 = Type::from<int>();
    Type* type2 = Type::from<Type>();
    
    ASSERT(type1->get_name() == "int");
    ASSERT(type2->get_name() == "reflect::Type");
}

void test_type_add_pointer() {
    Type* type1 = Type::from<int>();
    Type* type2 = Type::from<int*>();
    
    ASSERT(type1->add_pointer() == type2);
}

void test_type_remove_pointer() {
    Type* type1 = Type::from<int>();
    Type* type2 = Type::from<int*>();
    
    ASSERT(type2->remove_pointer() == type1);
}

void _from_unreflected() {
    Type::from<UnreflectedType>();
}

void _frominstance_unreflected() {
    Type::from_instance(new UnreflectedType());
}

void _fromname_unreflected() {
    Type::from_name("UnreflectedType");
}

void test_invalid_type() {
    ASSERT_THROWS(not_reflected, _from_unreflected);
    ASSERT_THROWS(not_reflected, _frominstance_unreflected);
    ASSERT_THROWS(not_reflected, _fromname_unreflected);
}

void run_type_tests() {
    TEST(test_type_from)
    TEST(test_type_name)
    TEST(test_type_add_pointer)
    TEST(test_type_remove_pointer)
    TEST(test_invalid_type)
}

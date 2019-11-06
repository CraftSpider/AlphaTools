
#include "at_tests"
#include "utils/sfinae.h"
#include "test_sfinae.h"

void A() {}

struct B {
    void C() {}
};

void test_typefinder() {
    typedef util::TypeFinder<decltype(&A)> FuncFinder;
    typedef util::TypeFinder<B> ClassFinder;
    typedef util::TypeFinder<decltype(&B::C)> MethodFinder;
    typedef util::TypeFinder<B*> PtrFinder;

    ASSERT(FuncFinder::function);
    ASSERT(!FuncFinder::cls && !FuncFinder::method && !FuncFinder::pointer);

    ASSERT(ClassFinder::cls);
    ASSERT(!ClassFinder::function && !ClassFinder::method && !ClassFinder::pointer);

    ASSERT(MethodFinder::method);
    ASSERT(!MethodFinder::cls && !MethodFinder::function && !MethodFinder::pointer);

    ASSERT(PtrFinder::pointer);
    ASSERT(!PtrFinder::cls && !PtrFinder::method && !PtrFinder::function);

}

void test_makeptr() {
    typedef util::MakePtr<int>::type Type1;
    typedef util::MakePtr<int*>::type Type2;

    int a = 1;

    ASSERT(typeid(Type1) == typeid(Type2));
    ASSERT(util::MakePtr<int>::make_ptr(a) == &a);
    ASSERT(util::MakePtr<int*>::make_ptr(&a) == &a);
}

void run_sfinae_tests() {
    TEST(test_typefinder)
    TEST(test_makeptr)
}

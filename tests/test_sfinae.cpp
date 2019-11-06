
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

    ASSERT((std::is_same<Type1, Type2>::value));
    ASSERT(util::MakePtr<int>::make_ptr(a) == &a);
    ASSERT(util::MakePtr<int*>::make_ptr(&a) == &a);
}

void test_functiontraits() {
    typedef util::FunctionTraits<decltype(A)> Traits;
    typedef util::FunctionTraits<decltype(&A)> Traits2;
    typedef util::FunctionTraits<int> Invalid;
    
    ASSERT(Traits::valid && !Traits::invalid);
    ASSERT((std::is_same<Traits::return_type, void>::value));
    ASSERT((std::is_same<Traits::raw_type, void()>::value));
    ASSERT((std::is_same<Traits::pointer_type, void(*)()>::value));
    ASSERT(Traits::num_args == 0);
    
    ASSERT(Traits2::valid && !Traits2::invalid);
    ASSERT((std::is_same<Traits2::return_type, void>::value));
    ASSERT((std::is_same<Traits2::raw_type, void()>::value));
    ASSERT((std::is_same<Traits2::pointer_type, void(*)()>::value));
    ASSERT(Traits2::num_args == 0);
    
    ASSERT(!Invalid::valid && Invalid::invalid);
}

void test_methodtraits() {
    typedef util::MethodTraits<decltype(&B::C)> Traits;
    typedef util::MethodTraits<int> Invalid;
    
    ASSERT(Traits::valid && !Traits::invalid);
    ASSERT((std::is_same<Traits::class_type, B>::value));
    ASSERT((std::is_same<Traits::return_type, void>::value));
    ASSERT(Traits::num_args == 0);
    
    ASSERT(!Invalid::valid && Invalid::invalid);
    ASSERT((std::is_same<Invalid::class_type, void>::value));
}

void run_sfinae_tests() {
    TEST(test_typefinder)
    TEST(test_makeptr)
    TEST(test_functiontraits)
    TEST(test_methodtraits)
}

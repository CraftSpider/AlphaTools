
#include "at_tests"
#include "utils/sfinae.h"
#include "test_sfinae.h"

void A() {}

struct B {
    float D;
    void C() {}
};

struct E {
    float F;
    int G;
};

void test_typefinder() {
    typedef util::TypeFinder<int> NumericFinder1;
    typedef util::TypeFinder<double> NumericFinder2;
    typedef util::TypeFinder<int[2]> ArrayFinder;
    typedef util::TypeFinder<B> ClassFinder;
    typedef util::TypeFinder<decltype(&A)> FuncFinder;
    typedef util::TypeFinder<decltype(&B::D)> DataFinder;
    typedef util::TypeFinder<decltype(&B::C)> MethodFinder;

    ASSERT(NumericFinder1::numeric);
    ASSERT(!NumericFinder1::array && !NumericFinder1::cls && !NumericFinder1::function && !NumericFinder1::member_data && !NumericFinder1::member_func);
    
    ASSERT(NumericFinder2::numeric);
    ASSERT(!NumericFinder2::array && !NumericFinder2::cls && !NumericFinder2::function && !NumericFinder2::member_data && !NumericFinder2::member_func);
    
    ASSERT(ArrayFinder::array);
    ASSERT(!ArrayFinder::numeric && !ArrayFinder::cls && !ArrayFinder::function && !ArrayFinder::member_data && !ArrayFinder::member_func);
    
    ASSERT(FuncFinder::function);
    ASSERT(!FuncFinder::array && !FuncFinder::cls && !FuncFinder::numeric && !FuncFinder::member_data && !FuncFinder::member_func);

    ASSERT(ClassFinder::cls);
    ASSERT(!ClassFinder::array && !ClassFinder::numeric && !ClassFinder::function && !ClassFinder::member_data && !ClassFinder::member_func);
    
    ASSERT(DataFinder::member_data);
    ASSERT(!DataFinder::array && !DataFinder::cls && !DataFinder::function && !DataFinder::numeric && !DataFinder::member_func);
    
    ASSERT(MethodFinder::member_func);
    ASSERT(!MethodFinder::array && !MethodFinder::cls && !MethodFinder::function && !MethodFinder::member_data && !MethodFinder::numeric);

}

void test_makeptr() {
    typedef util::MakePtr<int>::type Type1;
    typedef util::MakePtr<int*>::type Type2;

    int a = 1;

    ASSERT((std::is_same<Type1, Type2>::value));
    ASSERT(util::MakePtr<int>::make_ptr(a) == &a);
    ASSERT(util::MakePtr<int*>::make_ptr(&a) == &a);
}

void test_derefptr() {
    typedef util::DerefPointer<int> Type1;
    typedef util::DerefPointer<int*> Type2;
    typedef util::DerefPointer<int**> Type3;
    
    typedef util::DerefPointer<void()>::type Type4;
    typedef util::DerefPointer<void(*)()>::type Type5;
    
    typedef util::DerefPointer<void(B::*)()>::type Type6;
    typedef util::DerefPointer<void(B::**)()>::type Type7;
    
    ASSERT((std::is_same<Type1::type, int>::value));
    ASSERT((std::is_same<Type2::type, int>::value));
    ASSERT((std::is_same<Type3::type, int>::value));
    ASSERT(Type1::depth == 0);
    ASSERT(Type2::depth == 1);
    ASSERT(Type3::depth == 2);
    
    ASSERT((std::is_same<Type4, void()>::value));
    ASSERT((std::is_same<Type5, void()>::value));
    
    ASSERT((std::is_same<Type6, void(B::*)()>::value));
    ASSERT((std::is_same<Type7, void(B::*)()>::value));
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

void test_membertraits() {
    typedef util::MemberTraits<decltype(&B::D)> Traits;
    typedef util::MemberTraits<float> Invalid;
    
    ASSERT(Traits::valid && !Traits::invalid);
    ASSERT((std::is_same<Traits::class_type, B>::value));
    ASSERT((std::is_same<Traits::member_type, float>::value));
    
    ASSERT(!Invalid::valid && Invalid::invalid);
    ASSERT((std::is_same<Invalid::class_type, void>::value));
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

void test_rawdata() {
    typedef util::RawData<E> RawE;
    static constexpr uchar expected[] = {0x04, 0x02, 0x02, 0x04, 0x03, 0x01, 0x01, 0x03};
    
    E temp = E();
    RawE raw_temp = RawE(temp);
    
    temp.F = 1.5282352E-36f;
    temp.G = 50397443;
    
    for (size_t i = 0; i < RawE::size; ++i) {
        ASSERT(raw_temp[i] == expected[i]);
    }
    
    ASSERT(raw_temp.get_value<int>(0) == 67240452);
    ASSERT(raw_temp.get_value<float>(4) == 3.7910854E-37f);
    
    raw_temp.set_value<int>(0, 16908801);
    raw_temp.set_value<float>(4, 2.4063055E-38f);
    
    ASSERT(temp.F == 2.3878667E-38f);
    ASSERT(temp.G == 16974593);
    
    try {
        raw_temp[RawE::size];
        testing::fail("Access beyond size didn't throw error");
    } catch (std::out_of_range&) {}
}

void run_sfinae_tests() {
    TEST(test_typefinder)
    TEST(test_makeptr)
    TEST(test_derefptr)
    TEST(test_membertraits)
    TEST(test_functiontraits)
    TEST(test_methodtraits)
    TEST(test_rawdata)
}

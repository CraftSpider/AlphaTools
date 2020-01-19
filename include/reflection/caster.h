#pragma once

#include "variant.h"

namespace reflect {


typedef Variant(*CastFuncRef)(Variant&);


namespace CastType {

enum type {
    DYNAMIC,
    REINTERPRET,
    STATIC,
    CONST,
    C
};

std::string to_string(type t);

}


template<typename T>
class ShifterMeta {
public:
    
    static Variant add_pointer(Variant& obj);
    
    template<typename K>
    static std::enable_if_t<std::is_pointer_v<K>, Variant> remove_pointer(Variant& obj);
    
    template<typename K>
    static std::enable_if_t<!std::is_pointer_v<K>, Variant> remove_pointer(Variant& obj);
    
    static CastFuncRef get_add_pointer_func();
    
    static CastFuncRef get_remove_pointer_func();
    
};

template<typename From, typename To>
class __CastSupport {
    
    template<typename T, typename K, typename = decltype(dynamic_cast<K>(std::declval<T>()))>
    static std::true_type __test_dynamic(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_dynamic(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(reinterpret_cast<K>(std::declval<T>()))>
    static std::true_type __test_reinterpret(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_reinterpret(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(static_cast<K>(std::declval<T>()))>
    static std::true_type __test_static(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_static(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(const_cast<K>(std::declval<T>()))>
    static std::true_type __test_const(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_const(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype((K)(std::declval<T>()))>
    static std::true_type __test_c(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_c(...) {return std::false_type();}
    
public:
    
    enum {
        support_dynamic = std::is_same<decltype(__test_dynamic<From, To>(0)), std::true_type>::value,
        support_reinterpret = std::is_same<decltype(__test_reinterpret<From, To>(0)), std::true_type>::value,
        support_static = std::is_same<decltype(__test_static<From, To>(0)), std::true_type>::value,
        support_const = std::is_same<decltype(__test_const<From, To>(0)), std::true_type>::value,
        support_c = std::is_same<decltype(__test_c<From, To>(0)), std::true_type>::value,
    };
};

template<typename T, typename K>
class CasterMeta {
    
    using CastCheck = __CastSupport<T, K>;
    
public:
    
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_dynamic, Variant> cast_dynamic(Variant& obj);
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_dynamic, Variant> cast_dynamic(Variant& obj);
    
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_reinterpret, Variant> cast_reinterpret(Variant& obj);
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_reinterpret, Variant> cast_reinterpret(Variant& obj);
    
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_static, Variant> cast_static(Variant& obj);
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_static, Variant> cast_static(Variant& obj);
    
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_const, Variant> cast_const(Variant& obj);
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_const, Variant> cast_const(Variant& obj);
    
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_c, Variant> cast_c(Variant& obj);
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_c, Variant> cast_c(Variant& obj);
    
    static CastFuncRef get_cast_dynamic_func();
    
    static CastFuncRef get_cast_reinterpret_func();
    
    static CastFuncRef get_cast_static_func();
    
    static CastFuncRef get_cast_const_func();
    
    static CastFuncRef get_cast_c_func();
    
};

class TypeCaster final {
    
    CastFuncRef dynamic_ptr, reinterpret_ptr, static_ptr, const_ptr, c_ptr;
    
    Type* from_type;
    Type* to_type;
    
    template<typename T, typename K>
    explicit TypeCaster(CasterMeta<T, K>);
    
public:
    
    TypeCaster(TypeCaster&) = delete;
    TypeCaster(TypeCaster&&) = delete;
    
    template<typename T, typename K>
    static TypeCaster& from();
    
    Variant cast(Variant& variant, CastType::type type = CastType::C);
    
    Type* get_from_type();
    
    Type* get_to_type();
    
};

class Caster final {
    
    CastFuncRef add_ptr, remove_ptr;
    
    Type* type;
    
    std::map<Type*, TypeCaster*> registered_casts;
    
    template<typename T>
    explicit Caster(ShifterMeta<T>);
    
    ~Caster() = default;

public:
    
    Caster(Caster&) = delete;
    Caster(Caster&&) = delete;
    
    template<typename T>
    static Caster& from();
    
    template<typename T, typename K>
    void __add_cast();
    
    Variant add_pointer(Variant variant);
    
    Variant remove_pointer(Variant variant);
    
    Variant cast(Type* type, Variant variant, CastType::type cast = CastType::C);
    
    Type* get_type();
    
};

}

#include "caster.tpp"

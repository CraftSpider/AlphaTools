#pragma once

#include "variant.h"

namespace reflect {


typedef Variant(*CastFuncRef)(Variant&);


enum class CastType {
    DYNAMIC,
    REINTERPRET,
    STATIC,
    CONST,
    C
};


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

template<typename T, typename K>
class CasterMeta {
public:
    
    static Variant cast_dynamic(Variant& obj);
    
    static Variant cast_reinterpret(Variant& obj);
    
    static Variant cast_static(Variant& obj);
    
    static Variant cast_const(Variant& obj);
    
    static Variant cast_c(Variant& obj);
    
    static CastFuncRef get_cast_dynamic_func();
    
    static CastFuncRef get_cast_reinterpret_func();
    
    static CastFuncRef get_cast_static_func();
    
    static CastFuncRef get_cast_const_func();
    
    static CastFuncRef get_cast_c_func();
    
};

class TypeCaster final {
    
    CastFuncRef dynamic_ptr, reinterpret_ptr, static_ptr, const_ptr, c_ptr;
    
    template<typename T, typename K>
    explicit TypeCaster(CasterMeta<T, K>);
    
public:
    
    TypeCaster(TypeCaster&) = delete;
    TypeCaster(TypeCaster&&) = delete;
    
    template<typename T, typename K>
    static TypeCaster& from();
    
    Variant cast(Variant& variant, CastType type = CastType::C);
    
};

class Caster final {
    
    CastFuncRef add_ptr, remove_ptr;
    
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
    void __add_cast(CasterMeta<T, K> meta);
    
    Variant add_pointer(Variant variant);
    
    Variant remove_pointer(Variant variant);
    
    Variant cast(Type* type, Variant variant, CastType cast = CastType::C);
    
};

}

#include "caster.tpp"

#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file member_prop.h
 * \brief Reflection support for Member Properties
 */

namespace reflect {

typedef Variant(*MemberPropertyGetFuncRef)(void* ptr, Variant&);
typedef void(*MemberPropertySetFuncRef)(void* ptr, Variant&, Variant&);

template<typename T, typename Ret>
class MemberPropertyMeta {
public:
    
    static Variant get(Ret T::** ptr, Variant& instance);
    
    static void set(Ret T::** ptr, Variant& instance, Variant& data);
    
    static MemberPropertyGetFuncRef get_get_func();
    
    static MemberPropertySetFuncRef get_set_func();

};

class MemberProperty final {

    Type* type;
    Type* property_type;
    std::string name;
    
    void* ptr;
    MemberPropertyGetFuncRef get_ptr;
    MemberPropertySetFuncRef set_ptr;
    
    template<typename T, typename Ret>
    MemberProperty(Ret T::* ptr, std::string name);
    ~MemberProperty() = default;
    
public:
    
    MemberProperty(MemberProperty&) = delete;
    MemberProperty(MemberProperty&&) = delete;
    
    template<typename T, typename Ret>
    static MemberProperty& from(Ret T::* ptr, std::string name);
    
    Variant get(Variant instance);
    
    void set(Variant instance, Variant value);
    
    Type* get_type();
    
    Type* get_property_type();
    
    std::string get_name();

};

}

#include "member_prop.tpp"

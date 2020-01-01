#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file static_prop.h
 * \brief Reflection support for Static Properties
 */

namespace reflect {

typedef Variant(*StaticPropertyGetFuncRef)(void*);
typedef void(*StaticPropertySetFuncRef)(void*, Variant&);

template<typename Ret>
class StaticPropertyMeta {
public:
    
    static Variant get(Ret* ptr);
    
    static void set(Ret* ptr, Variant& data);
    
    static StaticPropertyGetFuncRef get_get_func();
    
    static StaticPropertySetFuncRef get_set_func();
    
};

class StaticProperty final {

    Type* type;
    Type* property_type;
    std::string name;
    
    void* ptr;
    StaticPropertyGetFuncRef get_ptr;
    StaticPropertySetFuncRef set_ptr;
    
    template<typename Ret>
    StaticProperty(Type* type, Ret* ptr, std::string name);
    ~StaticProperty() = default;
    
public:
    
    StaticProperty(StaticProperty&) = delete;
    StaticProperty(StaticProperty&&) = delete;
    
    template<typename T, typename Ret>
    static StaticProperty& from(Ret* ptr, std::string name);
    
    Variant get();
    
    void set(Variant data);
    
    Type* get_type();
    
    Type* get_property_type();
    
    std::string get_name();

};

}

#include "static_prop.tpp"

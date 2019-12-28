#pragma once

#include "type.h"
#include "variant.h"

namespace reflect {

typedef void(*MemberFunctionFuncRef)(Variant, std::vector<Variant>, Variant&);

template<typename T, typename Ret, typename... Args>
class MemberFunctionMeta {
public:
    
    static constexpr size_t num_args = sizeof...(Args);
    
    static Type* get_return_type();
    
    static std::vector<Type*> get_arg_types();
    
    static void invoke(Variant instance, std::vector<Variant> args, Variant& out);
    
    static MemberPropertyFuncRef get_invoke_func();
    
};

class MemberFunction {
    
    Type* type;
    Type* return_type;
    std::vector<Type*> arg_types;
    
    MemberPropertyFuncRef ptr;
    size_t num_args;
    
    template<typename T, typename Ret, typename... Args>
    MemberProperty(MemberPropertyMeta<T, Ret, Args...> meta);

public:
    
    template<typename T, typename Ret, typename... Args>
    static MemberProperty& from();
    
    Variant invoke(Variant instance, std::vector<Variant> args);
    
    Type* get_type();
    
    Type* get_return_type();
    
    const std::vector<Type*> get_arg_types();
    
    size_t get_num_args();
    
};

}

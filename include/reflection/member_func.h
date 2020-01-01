#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file member_func.h
 * \brief Reflection support for Member Functions
 */

namespace reflect {

typedef Variant(*MemberFunctionFuncRef)(void*, Variant&, std::vector<Variant>&);

template<typename T, typename Ret, typename... Args>
class MemberFunctionMeta {
public:
    
    static Variant invoke(Ret(T::**ptr)(Args...), Variant& instance, std::vector<Variant>& args);
    
    static MemberFunctionFuncRef get_invoke_func();
    
};

class MemberFunction final {
    
    Type* type;
    Type* return_type;
    std::vector<Type*> arg_types;
    std::string name;
    
    void* ptr;
    MemberFunctionFuncRef invoke_ptr;
    size_t num_args;
    
    template<typename T, typename Ret, typename... Args>
    MemberFunction(Ret(T::*ptr)(Args...), std::string name);
    ~MemberFunction() = default;

public:
    
    MemberFunction(MemberFunction&) = delete;
    MemberFunction(MemberFunction&&) = delete;
    
    template<typename T, typename Ret, typename... Args>
    static MemberFunction& from(Ret (T::*ptr)(Args...), std::string name);
    
    Variant invoke(Variant instance);
    
    Variant invoke(Variant instance, std::vector<Variant> args);
    
    Type* get_type();
    
    Type* get_return_type();
    
    const std::vector<Type*>& get_arg_types();
    
    size_t get_num_args();
    
    std::string get_name();
    
};

}

#include "member_func.tpp"

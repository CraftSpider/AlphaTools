#pragma once

#include "type.h"
#include "variant.h"

namespace reflect {

typedef Variant(*StaticFunctionFuncRef)(void(*)(), std::vector<Variant>&);

template<typename Ret, typename... Args>
class StaticFunctionMeta {
public:
    
    static Variant invoke(Ret(*ptr)(Args...), std::vector<Variant>& args);
    
    static StaticFunctionFuncRef get_invoke_func();
    
};

class StaticFunction {
    
    Type* type;
    Type* return_type;
    std::vector<Type*> arg_types;
    std::string name;
    
    void(*ptr)();
    StaticFunctionFuncRef invoke_ptr;
    size_t num_args;
    
    template<typename Ret, typename... Args>
    StaticFunction(Type* type, Ret(*ptr)(Args...), std::string name);
    
public:
    
    StaticFunction(StaticFunction&) = delete;
    StaticFunction(StaticFunction&&) = delete;
    
    template<typename T, typename Ret, typename... Args>
    static StaticFunction& from(Ret(*ptr)(Args...), std::string name);
    
    Variant invoke(std::vector<Variant> args);
    
    Type* get_type();
    
    Type* get_return_type();
    
    const std::vector<Type*>& get_arg_types();
    
    size_t get_num_args();
    
    std::string get_name();
    
};

}

#include "static_func.tpp"

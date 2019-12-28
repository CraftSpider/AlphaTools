#pragma once

#include <vector>
#include "type.h"
#include "errors.h"
#include "variant.h"
#include "utils/sfinae.h"

namespace reflect {

typedef void*(*ConstructFuncRef)(std::vector<Variant>);

template<typename T, typename... Args>
class ConstructorMeta {
public:
    
    static constexpr size_t num_args = sizeof...(Args);
    
    static std::vector<Type*> get_arg_types();
    
    static T* construct(std::vector<Variant> args);
    
    static ConstructFuncRef get_construct_func();
    
};

class Constructor {
    
    Type *type;
    std::vector<Type *> arg_types;
    
    ConstructFuncRef ptr;
    size_t num_args;
    
    template<typename T, typename... Args>
    explicit Constructor(ConstructorMeta<T, Args...> meta);
    
public:
    
    template<typename T, typename... Args>
    static Constructor& from();
    
    Variant construct(std::vector<Variant> args);
    
    Type* get_type();
    
    size_t get_num_args();
    
};

}

#include "constructor.tpp"

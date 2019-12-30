#pragma once

#include <vector>
#include "type.h"
#include "errors.h"
#include "variant.h"
#include "utils/sfinae.h"

/**
 * \file constructor.h
 * \brief Reflection support for class constructors
 */

namespace reflect {

typedef void*(*ConstructFuncRef)(std::vector<Variant>&);

template<typename T, typename... Args>
class ConstructorMeta {
public:
    
    static T* construct(std::vector<Variant>& args);
    
    static ConstructFuncRef get_construct_func();
    
};

class Constructor final {
    
    Type *type;
    std::vector<Type*> arg_types;
    
    ConstructFuncRef ptr;
    size_t num_args;
    
    template<typename T, typename... Args>
    explicit Constructor(ConstructorMeta<T, Args...> meta);
    
public:
    
    Constructor(Constructor&) = delete;
    Constructor(Constructor&&) = delete;
    
    template<typename T, typename... Args>
    static Constructor& from();
    
    Variant construct();
    
    Variant construct(std::vector<Variant> args);
    
    void* construct_unsafe(std::vector<Variant> args);
    
    Type* get_type();
    
    const std::vector<Type*>& get_arg_types();
    
    size_t get_num_args();
    
};

}

#include "constructor.tpp"

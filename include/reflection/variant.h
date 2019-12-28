#pragma once

#include "type.h"

namespace reflect {

class Variant final {
    
    Type* type = nullptr;
    void* data = nullptr;
    
    Variant() = default;

public:
    
    template<typename T>
    static Variant from_instance(T* obj);
    
    template<typename T>
    static Variant from_instance(T& obj);
    
    template<typename T>
    static Variant from_instance(T obj);
    
    static Variant from_type(Type* type);
    
    static Variant from_pair(Type* type, void* data);
    
    Type* get_type();
    
    void* get_value_unsafe();
    
    template<typename T>
    typename std::remove_reference_t<T>* get_value_ptr();
    
    template<typename T>
    typename std::remove_reference_t<T>& get_value_ref();
    
    template<typename T>
    T get_value();
    
};

}

#include "variant.tpp"
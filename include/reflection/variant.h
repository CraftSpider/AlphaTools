#pragma once

#include "type.h"

/**
 * \file variant.h
 * \brief A generic container for a value of any type. Can refcount itself or not
 */

namespace reflect {

class Variant final {
    
    static std::map<void*, size_t> refcount;
    
    Type* type = nullptr;
    void* data = nullptr;
    bool owned = false;
    
    Variant() = default;
    
    static void increment_refcount(void* data);
    static void decrement_refcount(void* data);
    static size_t get_refcount(void* data);

public:
    
    Variant(const Variant& other);
    
    Variant(Variant&& other) noexcept;
    
    ~Variant();
    
    template<typename T>
    static Variant from_ptr(T* obj);
    
    template<typename T>
    static Variant from_ref(T& obj);
    
    template<typename T>
    static Variant from_instance(T obj);
    
    template<typename T>
    static Variant from_return(T obj);
    
    static Variant from_type(Type* type);
    
    static Variant from_pair(Type* type, void* data);
    
    static Variant from_pair_owned(Type* type, void* data);
    
    Type* get_type();
    
    void* get_value_unsafe();
    
    /**
     * Get the value contained in this Variant as a pointer
     * Warning: If this Variant owns the pointer, for example in the case of the result of a construct call,
     * then the pointer will only live as long as this Variant does. Either copy the value, or use take_value_ptr.
     * \tparam T Type to retrieve pointer as
     * \return Pointer to instance of type T
     */
    template<typename T>
    typename std::remove_reference_t<T>* get_value_ptr();
    
    template<typename T>
    typename std::remove_reference_t<T>& get_value_ref();
    
    void* take_value_unsafe();
    
    template<typename T>
    typename std::remove_reference_t<T>* take_value_ptr();
    
    template<typename T>
    typename std::remove_reference_t<T>& take_value_ref();
    
    template<typename T>
    T get_value();
    
    bool get_owned();
    
};

}

#include "variant.tpp"

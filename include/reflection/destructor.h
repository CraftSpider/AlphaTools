#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file destructor.h
 * \brief Reflection support for type destructors
 */

namespace reflect {

/**
 * Generic type all destruct functions can be cast to
 */
typedef void(*DestructFuncRef)(void*);

/**
 * \internal
 *
 * Class to generate type-safe and well-formed destruction of a class
 *
 * \tparam T Class to destruct
 */
template<typename T>
class DestructorMeta {
public:
    
    /**
     * Destruct an instance of the class
     *
     * \param instance Instance to destruct
     * \return void
     */
    static void destruct(typename std::remove_reference_t<T>* instance);
    
    /**
     * Get the destruct func as a common type
     *
     * \return Destruct function pointer
     */
    static DestructFuncRef get_destruct_func();
    
};

/**
 * Class that wraps a type destructor. Can be used to delete instances of the type
 */
class Destructor final {
    
    Type* type;
    
    DestructFuncRef ptr;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type to destruct
     * \param meta Meta to get functions from
     */
    template<typename T>
    explicit Destructor(DestructorMeta<T> meta);
    
    /**
     * As Destructors have a static lifetime, prevent external things from
     * deleting them
     */
    ~Destructor() = default;
    
public:
    
    /**
     * Destructors should never be copied, they are singleton
     */
    Destructor(Destructor&) = delete;
    
    /**
     * Destructors should never be moved, they are singleton
     */
    Destructor(Destructor&&) = delete;
    
    /**
     * Get the destructor associated with a given type and set of argument types
     *
     * \tparam T Type to destruct
     * \return Destructor instance for that type
     */
    template<typename T>
    static Destructor& from();
    
    /**
     * Safely destruct an instance of a type, with checking for type-safety and allocation strategy
     *
     * \param instance Instance to destruct
     */
    void destruct(Variant instance);
    
    /**
     * Unsafely destruct a void pointer. Assumes it is of the right type and is not being externally managed
     *
     * \param instance Instance to destruct
     */
    void unsafe_destruct(void* instance);
    
    /**
     * Get the Type that is associated with this Destructor
     *
     * \return Type that is destructed
     */
    Type* get_type();
    
};

}

#include "destructor.tpp"

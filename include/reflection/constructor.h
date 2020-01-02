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

/**
 * Generic type all meta construct functions can be cast to
 */
typedef void*(*ConstructFuncRef)(std::vector<Variant>&);

/**
 * \internal
 *
 * Class to generate type-safe and well-formed construction of a class
 *
 * \tparam T Class to construct
 * \tparam Args Arguments to constructor
 */
template<typename T, typename... Args>
class ConstructorMeta {
public:
    
    /**
     * Construct and return a new instance of the class
     *
     * \param args Arguments to construct with
     * \return New instance
     */
    static T* construct(std::vector<Variant>& args);
    
    /**
     * Get the construct function as a common type
     *
     * \return Construct function pointer
     */
    static ConstructFuncRef get_construct_func();
    
};

/**
 * Class that wraps a type constructor. Can be used to create new instances of that type.
 */
class Constructor final {
    
    Type *type;
    std::vector<Type*> arg_types;
    
    ConstructFuncRef ptr;
    size_t num_args;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type to construct
     * \tparam Args Arguments to constructor
     * \param meta Meta to get functions from
     */
    template<typename T, typename... Args>
    explicit Constructor(ConstructorMeta<T, Args...> meta);
    
    /**
     * As Constructors have a static lifetime, prevent external things from
     * deleting them
     */
    ~Constructor() = default;
    
public:
    
    /**
     * Constructors should never be copied, they are singleton
     */
    Constructor(Constructor&) = delete;
    
    /**
     * Constructors should never be moved, they are singleton
     */
    Constructor(Constructor&&) = delete;
    
    /**
     * Get the constructor associated with a given type and set of argument types
     *
     * \tparam T Type to construct
     * \tparam Args Arguments to constructor
     * \return Constructor instance for that set of types
     */
    template<typename T, typename... Args>
    static Constructor& from();
    
    /**
     * Construct and return a new instance, if this is a no-arg constructor
     *
     * \return New type instance
     */
    Variant construct();
    
    /**
     * Construct and return a new instance, passing the given arguments to the constructor
     *
     * \param args Arguments to pass to the constructor
     * \return New type instance
     */
    Variant construct(std::vector<Variant> args);
    
    /**
     * Construct and return a new instance as a void pointer, passing the given
     * arguments to the constructor
     *
     * \param args Arguments to pass to the constructor
     * \return New type instance as a void pointer
     */
    void* construct_unsafe(std::vector<Variant> args);
    
    /**
     * Get the Type that is associated with this Constructor
     *
     * \return Type that is constructed
     */
    Type* get_type();
    
    /**
     * Get the list of argument types for this constructor
     *
     * \return Argument types
     */
    const std::vector<Type*>& get_arg_types();
    
    /**
     * Get the number of arguments that this constructor takes
     *
     * \return Argument number
     */
    size_t get_num_args();
    
};

}

#include "constructor.tpp"

#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file static_func.h
 * \brief Reflection support for Static Functions
 */

namespace reflect {

/**
 * Generic type all static invoke functions can be cast to
 */
typedef Variant(*StaticFunctionFuncRef)(void(*)(), std::vector<Variant>&);

/**
 * \internal
 *
 * Class to generate type-safe and well-formed invocation of a static function
 *
 * \tparam Ret Return type of function
 * \tparam Args Arguments to function
 */
template<typename Ret, typename... Args>
class StaticFunctionMeta {
public:
    
    /**
     * Invoke a static function of the given type
     *
     * \param ptr Pointer to a function
     * \param args Arguments to pass to the function
     * \return Return from invocation
     */
    static Variant invoke(Ret(*ptr)(Args...), std::vector<Variant>& args);
    
    /**
     * Get the invoke func as a common type
     *
     * \return Invoke function pointer
     */
    static StaticFunctionFuncRef get_invoke_func();
    
};

/**
 * Class that wraps a static function. Can be used to invoke that function
 */
class StaticFunction final {
    
    Type* type;
    Type* return_type;
    std::vector<Type*> arg_types;
    std::string name;
    
    void(*ptr)();
    StaticFunctionFuncRef invoke_ptr;
    size_t num_args;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam Ret Return type of the function
     * \tparam Args Argument types to the function
     * \param type Type the function is associated with
     * \param ptr Pointer to the function
     * \param name Name of the function
     */
    template<typename Ret, typename... Args>
    StaticFunction(Type* type, Ret(*ptr)(Args...), std::string name);
    
    /**
     * As StaticFunctions have a static lifetime, prevent external things from
     * deleting them
     */
    ~StaticFunction() = default;
    
public:
    
    /**
     * StaticFunctions should never be copied, they are singleton
     */
    StaticFunction(StaticFunction&) = delete;
    
    /**
     * StaticFunctions should never be moved, they are singleton
     */
    StaticFunction(StaticFunction&&) = delete;
    
    /**
     * Get the StaticFunction associated with a given member function pointer and name
     *
     * \tparam T Class the function is defined on
     * \tparam Ret Return type of the function
     * \tparam Args Argument types of the function
     * \param ptr Pointer to the function
     * \param name Name of the function
     * \return Associated StaticFunction instance
     */
    template<typename T, typename Ret, typename... Args>
    static StaticFunction& from(Ret(*ptr)(Args...), std::string name);
    
    /**
     * Invoke the static function, if this func is no-arg
     *
     * \return Return value of the function
     */
    Variant invoke();
    
    /**
     * Invoke the static function, passing the given arguments
     *
     * \param args Arguments to pass
     * \return Return value of the function
     */
    Variant invoke(std::vector<Variant> args);
    
    /**
     * Get the Type that is associated with this StaticFunction
     *
     * \return Associated Type
     */
    Type* get_type();
    
    /**
     * Get the return type of this StaticFunction
     *
     * \return Return type of the function
     */
    Type* get_return_type();
    
    /**
     * Get the list of argument types for this StaticFunction
     *
     * \return Argument types
     */
    const std::vector<Type*>& get_arg_types();
    
    /**
     * Get the number of arguments for this MemberFunction
     *
     * \return Argument number
     */
    size_t get_num_args();
    
    /**
     * Get the name of this MemberFunction
     *
     * \return Function name
     */
    std::string get_name();
    
};

}

#include "static_func.tpp"

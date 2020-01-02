#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file member_func.h
 * \brief Reflection support for Member Functions
 */

namespace reflect {

/**
 * Generic type all member invoke functions can be cast to
 */
typedef Variant(*MemberFunctionFuncRef)(void*, Variant&, std::vector<Variant>&);

/**
 * \internal
 *
 * Class to generate type-safe and well-formed invocation of a member function
 *
 * \tparam T Type to call member on
 * \tparam Ret Return type of member
 * \tparam Args Arguments to member function
 */
template<typename T, typename Ret, typename... Args>
class MemberFunctionMeta {
public:
    
    /**
     * Invoke a member function on an instance of the class
     *
     * \param ptr Pointer to member function pointer
     * \param instance Instance to invoke on
     * \param args Arguments to invoke with
     * \return Return from invocation
     */
    static Variant invoke(Ret(T::**ptr)(Args...), Variant& instance, std::vector<Variant>& args);
    
    /**
     * Get the invoke func as a common type
     *
     * \return Invoke function pointer
     */
    static MemberFunctionFuncRef get_invoke_func();
    
};

/**
 * Class that wraps a member function. Can be used to invoke that function on instance of the type
 */
class MemberFunction final {
    
    Type* type;
    Type* return_type;
    std::vector<Type*> arg_types;
    std::string name;
    
    void* ptr;
    MemberFunctionFuncRef invoke_ptr;
    size_t num_args;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type of the class
     * \tparam Ret Return type of the function
     * \tparam Args Argument types to the function
     * \param ptr Pointer to the function
     * \param name Name of the function
     */
    template<typename T, typename Ret, typename... Args>
    MemberFunction(Ret(T::*ptr)(Args...), std::string name);
    
    /**
     * As MemberFunctions have a static lifetime, prevent external things from
     * deleting them
     */
    ~MemberFunction() = default;

public:
    
    /**
     * MemberFunctions should never be copied, they are singleton
     */
    MemberFunction(MemberFunction&) = delete;
    
    /**
     * MemberFunctions should never be moved, they are singleton
     */
    MemberFunction(MemberFunction&&) = delete;
    
    /**
     * Get the MemberFunction associated with a given member function pointer and name
     *
     * \tparam T Type of the class
     * \tparam Ret Return type of the member function
     * \tparam Args Argument types to the member function
     * \param ptr Member function pointer
     * \param name Name of the function
     * \return Associated MemberFunction instance
     */
    template<typename T, typename Ret, typename... Args>
    static MemberFunction& from(Ret (T::*ptr)(Args...), std::string name);
    
    /**
     * Invoke the member function on an instance of the type, if this func is no-arg
     *
     * \param instance Instance to invoke on
     * \return Result of invocation
     */
    Variant invoke(Variant instance);
    
    /**
     * Invoke the member function on an instance of the type, passing the given arguments
     *
     * \param instance Instance to invoke on
     * \param args Arguments to pass
     * \return Result of invocation
     */
    Variant invoke(Variant instance, std::vector<Variant> args);
    
    /**
     * Get the Type that is associated with this MemberFunction
     *
     * \return Type invoked on
     */
    Type* get_type();
    
    /**
     * Get the return type associated with this MemberFunction
     *
     * \return Return type of the function
     */
    Type* get_return_type();
    
    /**
     * Get the list of argument types for this MemberFunction
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

#include "member_func.tpp"

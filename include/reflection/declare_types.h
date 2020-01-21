#pragma once

#include "at_macros"
#include "reflection/errors.h"
#include "reflection/type.h"
#include "reflection/variant.h"
#include "reflection/constructor.h"
#include "reflection/member_prop.h"
#include "reflection/member_func.h"
#include "reflection/static_prop.h"
#include "reflection/static_func.h"
#include "reflection/destructor.h"
#include "reflection/caster.h"

/**
 * \file declare_types.h
 * \brief Macros for declaring types as reflected
 */


/**
 * \brief Reflect a type
 *
 * Declares a type as reflected, and ensures all necessary things are initialized. Used in cpp files
 * This will automatically declare both reference and qualifiers for the type as well, though will not
 * automatically handle pointers to the type.
 * Must be matched by a DECLARE_TYPE_HEADER
 */
#define AT_DECLARE_TYPE(T) \
template<> \
std::string reflect::MetaType<T>::get_name() { \
    return #T; \
} \
template<> \
std::string reflect::MetaType<const T>::get_name() { \
    return "const " #T; \
} \
template<> \
std::string reflect::MetaType<volatile T>::get_name() { \
    return "volatile " #T; \
} \
template<> \
std::string reflect::MetaType<T&>::get_name() { \
    return #T "&"; \
} \
template<> \
std::string reflect::MetaType<const T&>::get_name() { \
    return "const " #T "&"; \
} \
template<> \
std::string reflect::MetaType<volatile T&>::get_name() { \
    return "volatile " #T "&"; \
} \
template<> \
std::string reflect::MetaType<T&&>::get_name() { \
    return #T "&&"; \
} \
template<> \
std::string reflect::MetaType<const T&&>::get_name() { \
    return "const " #T "&&"; \
} \
template<> \
std::string reflect::MetaType<volatile T&&>::get_name() { \
    return "volatile " #T "&&"; \
} \
static_block { \
    reflect::__MaybeConstructor<T>::add(); \
    reflect::__MaybeConstructor<T, T>::add(); \
    reflect::__MaybeConstructor<T, const T>::add(); \
    reflect::__MaybeConstructor<T, volatile T>::add(); \
    reflect::__MaybeConstructor<T, T&>::add(); \
    reflect::__MaybeConstructor<T, const T&>::add(); \
    reflect::__MaybeConstructor<T, volatile T&>::add(); \
    reflect::__MaybeConstructor<T, T&&>::add(); \
    reflect::__MaybeConstructor<T, const T&&>::add(); \
    reflect::__MaybeConstructor<T, volatile T&&>::add(); \
     \
    reflect::__MaybeDestructor<T>::set(); \
    reflect::__MaybeDestructor<const T>::set(); \
    reflect::__MaybeDestructor<volatile T>::set(); \
    reflect::__MaybeDestructor<T&>::set(); \
    reflect::__MaybeDestructor<const T&>::set(); \
    reflect::__MaybeDestructor<volatile T&>::set(); \
    reflect::__MaybeDestructor<T&&>::set(); \
    reflect::__MaybeDestructor<const T&&>::set(); \
    reflect::__MaybeDestructor<volatile T&&>::set(); \
     \
    reflect::Type::from<T>()->__set_caster(&reflect::Caster::from<T>()); \
}

/**
 * \brief Reflect a type's inheritance tree
 *
 * Declares a type as a parent for a type.
 * This will allow runtime resolution of functions
 * on the parent as well as mapping the type tree
 */
#define AT_DECLARE_PARENT(T, K) \
static_block { \
    reflect::Type::from<T>()->__add_parent_class( \
        reflect::Type::from<K>() \
    ); \
    reflect::Type::from<K>()->__add_child_class( \
        reflect::Type::from<T>() \
    ); \
}

/**
 * \brief Reflect a type's non-default constructors
 *
 * Declares non-default constructors for a type.
 * This will allow you to construct the type with the given args, through
 * the reflection system.
 */
#define AT_DECLARE_CONSTRUCTOR(T, ...) \
static_block { \
    reflect::Type::from<T>()->__add_constructor( \
        &reflect::Constructor::from<T, __VA_ARGS__>() \
    ); \
}

/**
 * \brief Reflect a type's data member by name
 *
 * Declares a data member of a type.
 * This will allow you to get and set this member on the type,
 * through the reflection system.
 */
#define AT_DECLARE_MEMBER_DATA(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_member_property( \
        &reflect::MemberProperty::from(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's member function by name
 *
 * Declares a member function of a type.
 * This will allow you to invoke and get the result of this member function
 * on the type, through the reflection system.
 */
#define AT_DECLARE_MEMBER_FUNC(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's member function with no args
 */
#define AT_DECLARE_MEMBER_FUNC_NOARG(T, NAME, RET) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from<T, RET>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's member function by name and arguments
 *
 * Declares a member function of a type.
 * This will allow you to invoke and get the result of this member function
 * on the type, through the reflection system.
 */
#define AT_DECLARE_MEMBER_FUNC_OVERLOAD(T, NAME, RET, ...) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from<T, RET, __VA_ARGS__>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's const member function by name
 *
 * Declares a member function of a type.
 * This will allow you to invoke and get the result of this member function
 * on the type, through the reflection system.
 */
#define AT_DECLARE_CONST_MEMBER_FUNC(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from_const(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's static data by name
 *
 * Declares a static property of a type.
 * This will allow you to get and set this property, through the reflection system.
 */
#define AT_DECLARE_STATIC_DATA(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_static_property( \
        &reflect::StaticProperty::from<T>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's static function by name
 *
 * Declares a static function of a type.
 * This will allow you to invoke and get the result of this static function,
 * through the reflection system.
 */
#define AT_DECLARE_STATIC_FUNC(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_static_function( \
        &reflect::StaticFunction::from<T>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's static function by name and arguments
 *
 * Declares a static function of a type.
 * This will allow you to invoke and get the result of this static function,
 * through the reflection system.
 */
#define AT_DECLARE_STATIC_FUNC_OVERLOAD(T, NAME, RET, ...) \
static_block { \
    reflect::Type::from<T>()->__add_static_function( \
        &reflect::StaticFunction::from<T, RET, __VA_ARGS__>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a cast operation between two types
 *
 * Declares a valid cast between two types.
 * This will allow dynamic casting from the first to the second
 * type, but not the other way around
 */
#define AT_DECLARE_TYPE_CAST(T, K) \
static_block { \
    reflect::Type::from<T>()->get_caster()->__add_cast<T, K>(); \
}

/**
 * \brief Reflect a type in the header
 *
 * Declares a type as reflected, used in header files.
 * Creates forward references to template specializations and any other
 * header necessities.
 * Must be matched by a DECLARE_TYPE
 */
#define AT_DECLARE_TYPE_HEADER(T) \
template<> \
std::string reflect::MetaType<T>::get_name(); \
template<> \
std::string reflect::MetaType<const T>::get_name(); \
template<> \
std::string reflect::MetaType<volatile T>::get_name(); \
template<> \
std::string reflect::MetaType<T&>::get_name(); \
template<> \
std::string reflect::MetaType<const T&>::get_name(); \
template<> \
std::string reflect::MetaType<volatile T&>::get_name(); \
template<> \
std::string reflect::MetaType<T&&>::get_name(); \
template<> \
std::string reflect::MetaType<const T&&>::get_name(); \
template<> \
std::string reflect::MetaType<volatile T&&>::get_name(); \

/**
 * \internal
 *
 * Special macro for allowing void as a type in cpp, as void is distinct from other types
 */
#define _AT_DECLARE_VOID() \
template<> \
std::string reflect::MetaType<void>::get_name() { \
    return "void"; \
}

/**
 * \internal
 *
 * Special macro for allowing void as a type in header, as void is distinct from other types
 */
#define _AT_DECLARE_VOID_HEADER() \
template<> \
std::string reflect::MetaType<void>::get_name();


#ifndef _AT_NO_MACRO

/**
 * Alias for AT_DECLARE_TYPE
 */
#define DECLARE_TYPE(T) AT_DECLARE_TYPE(T)

/**
 * Alias for AT_DECLARE_CONSTRUCTOR
 */
#define DECLARE_CONSTRUCTOR(T, ...) AT_DECLARE_CONSTRUCTOR(T, __VA_ARGS__)

/**
 * Alias for AT_DECLARE_MEMBER_DATA
 */
#define DECLARE_MEMBER_DATA(T, NAME) AT_DECLARE_MEMBER_DATA(T, NAME)

/**
 * Alias for AT_DECLARE_MEMBER_FUNC
 */
#define DECLARE_MEMBER_FUNC(T, NAME) AT_DECLARE_MEMBER_FUNC(T, NAME)

/**
 * Alias for AT_DECLARE_MEMBER_FUNC_NOARG
 */
#define DECLARE_MEMBER_FUNC_NOARG(T, NAME, RET) AT_DECLARE_MEMBER_FUNC_NOARG(T, NAME, RET)

/**
 * Alias for AT_DECLARE_MEMBER_FUNC_OVERLOAD
 */
#define DECLARE_MEMBER_FUNC_OVERLOAD(T, NAME, RET, ...) AT_DECLARE_MEMBER_FUNC_OVERLOAD(T, NAME, RET, __VA_ARGS__)

/**
 * Alias for AT_DECLARE_STATIC_DATA
 */
#define DECLARE_STATIC_DATA(T, NAME) AT_DECLARE_STATIC_DATA(T, NAME)

/**
 * Alias for AT_DECLARE_STATIC_FUNC
 */
#define DECLARE_STATIC_FUNC(T, NAME) AT_DECLARE_STATIC_FUNC(T, NAME)

/**
 * Alias for AT_DECLARE_STATIC_FUNC_OVERLOAD
 */
#define DECLARE_STATIC_FUNC_OVERLOAD(T, NAME, RET, ...) AT_DECLARE_STATIC_FUNC_OVERLOAD(T, NAME, RET, __VA_ARGS__)

/**
 * Alias for AT_DECLARE_TYPE_CAST
 */
#define DECLARE_TYPE_CAST(T, K) AT_DECLARE_TYPE_CAST(T, K)

/**
 * Alias for AT_DECLARE_TYPE_HEADER
 */
#define DECLARE_TYPE_HEADER(T) AT_DECLARE_TYPE_HEADER(T)

#endif


namespace reflect {

/**
 * \internal
 *
 * Type used to conditionally add a Constructor to a Type, if the constructor exists
 *
 * \tparam T Type to construct
 * \tparam Args Arguments to constructor
 */
template<typename T, typename... Args>
class __MaybeConstructor {
    
    /**
     * Specialization of adding the constructor for if it does exist
     * Adds the given Constructor to the Type
     *
     * \tparam K Type to construct
     * \tparam Args1 Arguments to constructor
     */
    template<typename K, typename... Args1>
    static std::enable_if_t<std::is_constructible_v<K, Args1...>, void> add_impl() {
        reflect::Type::from<K>()->__add_constructor(
            &reflect::Constructor::from<K, Args1...>()
        );
    }
    
    /**
     * Specialization of adding the constructor for if it doesn't exist
     * Does nothing
     *
     * \tparam K
     * \tparam Args1
     * \return
     */
    template<typename K, typename... Args1>
    static std::enable_if_t<!std::is_constructible_v<K, Args1...>, void> add_impl() {}
    
public:
    
    /**
     * Do work of adding the constructor
     *
     * \return void
     */
    static void add() {
        add_impl<T, Args...>();
    }
    
};

/**
 * \internal
 *
 * Type used to conditionally set the Destructor of a Type, if the destructor exists
 *
 * \tparam T Type to destruct
 */
template<typename T>
class __MaybeDestructor {
    
    /**
     * Specialization of adding the destructor for if it does exist
     * Sets the Destructor on the Type
     *
     * \tparam K Type to destruct
     */
    template<typename K>
    static std::enable_if_t<std::is_destructible_v<typename std::remove_reference_t<K>>, void> add_impl() {
        reflect::Type::from<K>()->__set_destructor(
            &reflect::Destructor::from<T>()
        );
    }
    
    /**
     * Specialization of adding the destructor for if it doesn't exist
     * Does nothing
     *
     * \tparam K Type to destruct
     */
    template<typename K>
    static std::enable_if_t<!std::is_destructible_v<typename std::remove_reference_t<K>>, void> add_impl() {}
    
public:
    
    /**
     * Do the work of setting the destructor
     *
     * \return void
     */
    static void set() {
        add_impl<T>();
    }
    
};

}

_AT_DECLARE_VOID_HEADER()

AT_DECLARE_TYPE_HEADER(char)
AT_DECLARE_TYPE_HEADER(short)
AT_DECLARE_TYPE_HEADER(int)
AT_DECLARE_TYPE_HEADER(long)
AT_DECLARE_TYPE_HEADER(long long)

AT_DECLARE_TYPE_HEADER(signed char)

AT_DECLARE_TYPE_HEADER(unsigned char)
AT_DECLARE_TYPE_HEADER(unsigned short)
AT_DECLARE_TYPE_HEADER(unsigned int)
AT_DECLARE_TYPE_HEADER(unsigned long)
AT_DECLARE_TYPE_HEADER(unsigned long long)

AT_DECLARE_TYPE_HEADER(bool)
AT_DECLARE_TYPE_HEADER(wchar_t)
AT_DECLARE_TYPE_HEADER(float)
AT_DECLARE_TYPE_HEADER(double)
AT_DECLARE_TYPE_HEADER(long double)
AT_DECLARE_TYPE_HEADER(nullptr_t)

AT_DECLARE_TYPE_HEADER(void*)
AT_DECLARE_TYPE_HEADER(char*)
AT_DECLARE_TYPE_HEADER(unsigned char*)

AT_DECLARE_TYPE_HEADER(std::string)
AT_DECLARE_TYPE_HEADER(std::runtime_error)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::Type*>)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::Constructor*>)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::MemberProperty*>)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::MemberFunction*>)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::StaticProperty*>)
AT_DECLARE_TYPE_HEADER(std::vector<reflect::StaticFunction*>)

AT_DECLARE_TYPE_HEADER(reflect::Type)
AT_DECLARE_TYPE_HEADER(reflect::Type*)
AT_DECLARE_TYPE_HEADER(reflect::Variant)
AT_DECLARE_TYPE_HEADER(reflect::Variant*)
AT_DECLARE_TYPE_HEADER(reflect::Constructor)
AT_DECLARE_TYPE_HEADER(reflect::Constructor*)
AT_DECLARE_TYPE_HEADER(reflect::MemberProperty)
AT_DECLARE_TYPE_HEADER(reflect::MemberProperty*)
AT_DECLARE_TYPE_HEADER(reflect::MemberFunction)
AT_DECLARE_TYPE_HEADER(reflect::MemberFunction*)
AT_DECLARE_TYPE_HEADER(reflect::StaticProperty)
AT_DECLARE_TYPE_HEADER(reflect::StaticProperty*)
AT_DECLARE_TYPE_HEADER(reflect::StaticFunction)
AT_DECLARE_TYPE_HEADER(reflect::StaticFunction*)
AT_DECLARE_TYPE_HEADER(reflect::Destructor)
AT_DECLARE_TYPE_HEADER(reflect::Destructor*)

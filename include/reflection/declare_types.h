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
#define DECLARE_TYPE(T) \
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
    reflect::__MaybeDestructor<T>::add(); \
    reflect::__MaybeDestructor<const T>::add(); \
    reflect::__MaybeDestructor<volatile T>::add(); \
    reflect::__MaybeDestructor<T&>::add(); \
    reflect::__MaybeDestructor<const T&>::add(); \
    reflect::__MaybeDestructor<volatile T&>::add(); \
    reflect::__MaybeDestructor<T&&>::add(); \
    reflect::__MaybeDestructor<const T&&>::add(); \
    reflect::__MaybeDestructor<volatile T&&>::add(); \
}

/**
 * \brief Reflect a type's non-default constructors
 *
 * Declares non-default constructors for a type.
 * This will allow you to construct the type with the given args, through
 * the reflection system.
 */
#define DECLARE_CONSTRUCTOR(T, ...) \
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
#define DECLARE_MEMBER_DATA(T, NAME) \
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
#define DECLARE_MEMBER_FUNC(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's member function with no args
 */
#define DECLARE_MEMBER_FUNC_NOARG(T, NAME, RET) \
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
#define DECLARE_MEMBER_FUNC_OVERLOAD(T, NAME, RET, ...) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from<T, RET, __VA_ARGS__>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type's static data by name
 *
 * Declares a static property of a type.
 * This will allow you to get and set this property, through the reflection system.
 */
#define DECLARE_STATIC_DATA(T, NAME) \
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
#define DECLARE_STATIC_FUNC(T, NAME) \
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
#define DECLARE_STATIC_FUNC_OVERLOAD(T, NAME, RET, ...) \
static_block { \
    reflect::Type::from<T>()->__add_static_function( \
        &reflect::StaticFunction::from<T, RET, __VA_ARGS__>(&T::NAME, #NAME) \
    ); \
}

/**
 * \brief Reflect a type in the header
 *
 * Declares a type as reflected, used in header files.
 * Creates forward references to template specializations and any other
 * header necessities.
 * Must be matched by a DECLARE_TYPE
 */
#define DECLARE_TYPE_HEADER(T) \
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
#define DECLARE_VOID() \
template<> \
std::string reflect::MetaType<void>::get_name() { \
    return "void"; \
}

/**
 * \internal
 *
 * Special macro for allowing void as a type in header, as void is distinct from other types
 */
#define DECLARE_VOID_HEADER() \
template<> \
std::string reflect::MetaType<void>::get_name();


namespace reflect {

template<typename T, typename... Args>
struct __MaybeConstructor {
    
    template<typename K, typename... Args1>
    static std::enable_if_t<std::is_constructible_v<K, Args1...>, void> add_impl() {
        reflect::Type::from<K>()->__add_constructor(
            &reflect::Constructor::from<K, Args1...>()
        );
    }
    
    template<typename K, typename... Args1>
    static std::enable_if_t<!std::is_constructible_v<K, Args1...>, void> add_impl() {}
    
    static void add() {
        add_impl<T, Args...>();
    }
    
};

template<typename T>
struct __MaybeDestructor {
    
    template<typename K>
    static std::enable_if_t<std::is_destructible_v<typename std::remove_reference_t<K>>, void> add_impl() {
        reflect::Type::from<K>()->__set_destructor(
            &reflect::Destructor::from<T>()
        );
    }
    
    template<typename K>
    static std::enable_if_t<!std::is_destructible_v<typename std::remove_reference_t<K>>, void> add_impl() {}
    
    static void add() {
        add_impl<T>();
    }
    
};

}

DECLARE_VOID_HEADER()

DECLARE_TYPE_HEADER(char)
DECLARE_TYPE_HEADER(short)
DECLARE_TYPE_HEADER(int)
DECLARE_TYPE_HEADER(long)
DECLARE_TYPE_HEADER(long long)

DECLARE_TYPE_HEADER(signed char)

DECLARE_TYPE_HEADER(unsigned char)
DECLARE_TYPE_HEADER(unsigned short)
DECLARE_TYPE_HEADER(unsigned int)
DECLARE_TYPE_HEADER(unsigned long)
DECLARE_TYPE_HEADER(unsigned long long)

DECLARE_TYPE_HEADER(bool)
DECLARE_TYPE_HEADER(wchar_t)
DECLARE_TYPE_HEADER(float)
DECLARE_TYPE_HEADER(double)
DECLARE_TYPE_HEADER(long double)
DECLARE_TYPE_HEADER(nullptr_t)

DECLARE_TYPE_HEADER(void*)
DECLARE_TYPE_HEADER(char*)
DECLARE_TYPE_HEADER(unsigned char*)

DECLARE_TYPE_HEADER(std::string)
DECLARE_TYPE_HEADER(std::runtime_error)
DECLARE_TYPE_HEADER(std::vector<reflect::Type*>)
DECLARE_TYPE_HEADER(std::vector<reflect::Constructor*>)
DECLARE_TYPE_HEADER(std::vector<reflect::MemberProperty*>)
DECLARE_TYPE_HEADER(std::vector<reflect::MemberFunction*>)
DECLARE_TYPE_HEADER(std::vector<reflect::StaticProperty*>)
DECLARE_TYPE_HEADER(std::vector<reflect::StaticFunction*>)

DECLARE_TYPE_HEADER(reflect::Type)
DECLARE_TYPE_HEADER(reflect::Type*)
DECLARE_TYPE_HEADER(reflect::Variant)
DECLARE_TYPE_HEADER(reflect::Variant*)
DECLARE_TYPE_HEADER(reflect::Constructor)
DECLARE_TYPE_HEADER(reflect::Constructor*)
DECLARE_TYPE_HEADER(reflect::MemberProperty)
DECLARE_TYPE_HEADER(reflect::MemberProperty*)
DECLARE_TYPE_HEADER(reflect::MemberFunction)
DECLARE_TYPE_HEADER(reflect::MemberFunction*)
DECLARE_TYPE_HEADER(reflect::StaticProperty)
DECLARE_TYPE_HEADER(reflect::StaticProperty*)
DECLARE_TYPE_HEADER(reflect::StaticFunction)
DECLARE_TYPE_HEADER(reflect::StaticFunction*)
DECLARE_TYPE_HEADER(reflect::Destructor)
DECLARE_TYPE_HEADER(reflect::Destructor*)

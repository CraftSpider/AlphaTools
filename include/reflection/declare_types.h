#pragma once

#include "at_macros"
#include "reflection/errors.h"
#include "reflection/type.h"
#include "reflection/variant.h"
#include "reflection/constructor.h"
#include "reflection/destructor.h"


/**
 * \brief Reflect a type
 *
 * Declares a type as reflected, and ensures all necessary things are initialized.
 * This will automatically declare both reference and qualifiers for the type as well, though will not
 * automatically handle pointers to the type.
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
    reflect::Type::from<T>()->__set_destructor( \
        &reflect::Destructor::from<T>() \
    ); \
    reflect::Type::from<const T>()->__set_destructor( \
        &reflect::Destructor::from<const T>() \
    ); \
    reflect::Type::from<volatile T>()->__set_destructor( \
        &reflect::Destructor::from<volatile T>() \
    ); \
    reflect::Type::from<T&>()->__set_destructor( \
        &reflect::Destructor::from<T&>() \
    ); \
    reflect::Type::from<const T&>()->__set_destructor( \
        &reflect::Destructor::from<const T&>() \
    ); \
    reflect::Type::from<volatile T&>()->__set_destructor( \
        &reflect::Destructor::from<volatile T&>() \
    ); \
    reflect::Type::from<T&&>()->__set_destructor( \
        &reflect::Destructor::from<T&&>() \
    ); \
    reflect::Type::from<const T&&>()->__set_destructor( \
        &reflect::Destructor::from<const T&&>() \
    ); \
    reflect::Type::from<volatile T&&>()->__set_destructor( \
        &reflect::Destructor::from<volatile T&&>() \
    ); \
}

/**
 * \brief Reflect a type's default constructor
 *
 * Declares a type as having a reflected default constructor.
 * This will allow you to zero-arg construct the type, through the reflection
 * system.
 */
#define DECLARE_DEFAULT_CONSTRUCTOR(T) \
static_block { \
    reflect::Type::from<T>()->__add_constructor( \
        &reflect::Constructor::from<T>() \
    ); \
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

#define DECLARE_MEMBER_DATA(T, NAME, K) \
static_block { \
    reflect::Type::from<T>()->__add_member_property( \
        &reflect::MemberProperty::from<T, K>(&T::NAME, #NAME) \
    ); \
}

#define DECLARE_MEMBER_FUNC(T, NAME, K, ...)

#define DECLARE_STATIC_DATA(T, NAME, K)

#define DECLARE_STATIC_FUNC(T, NAME, K, ...)


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


DECLARE_TYPE_HEADER(char)
DECLARE_TYPE_HEADER(short)
DECLARE_TYPE_HEADER(int)
DECLARE_TYPE_HEADER(long)
DECLARE_TYPE_HEADER(long long)

DECLARE_TYPE_HEADER(unsigned char)
DECLARE_TYPE_HEADER(unsigned short)
DECLARE_TYPE_HEADER(unsigned int)
DECLARE_TYPE_HEADER(unsigned long)
DECLARE_TYPE_HEADER(unsigned long long)

DECLARE_TYPE_HEADER(bool)
DECLARE_TYPE_HEADER(float)
DECLARE_TYPE_HEADER(double)
DECLARE_TYPE_HEADER(nullptr_t)

DECLARE_TYPE_HEADER(std::string)

DECLARE_TYPE_HEADER(reflect::Type)
DECLARE_TYPE_HEADER(reflect::Variant)
DECLARE_TYPE_HEADER(reflect::Constructor)

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

#define DECLARE_MEMBER_FUNC(T, NAME) \
static_block { \
    reflect::Type::from<T>()->__add_member_function( \
        &reflect::MemberFunction::from(&T::NAME, #NAME) \
    ); \
}

#define DECLARE_STATIC_DATA(T, NAME, K) \
static_block { \
    reflect::Type::from<T>()->__add_static_property( \
         \
    ) \
}

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

}


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

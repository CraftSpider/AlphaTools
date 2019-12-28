#pragma once

#include "at_macros"
#include "reflection/errors.h"
#include "reflection/type.h"
#include "reflection/variant.h"
#include "reflection/constructor.h"


#define DECLARE_TYPE(T) \
template<> \
std::string reflect::MetaType<T>::get_name() { \
    return #T; \
}

#define DECLARE_DEFAULT_CONSTRUCTOR(T) \
static_block { \
    reflect::Type::from<T>()->__add_constructor( \
        &reflect::Constructor::from<T>() \
    ); \
}

#define DECLARE_CONSTRUCTOR(T, ...) \
static_block { \
    reflect::Type::from<T>()->__add_constructor( \
        &reflect::Constructor::from<T, __VA_ARGS__>() \
    ); \
}


#define DECLARE_MEMBER_DATA(T, NAME, K)

#define DECLARE_MEMBER_FUNC(T, NAME, K, ...)

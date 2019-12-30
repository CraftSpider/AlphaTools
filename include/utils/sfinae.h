#pragma once

#include <type_traits>
#include "types.h"

/**
 * \file sfinae.h
 * \brief Various SFINAE utilities
 */

namespace util {

/**
 * Class that provides compile-time determination of a type. Seperates into class,
 * function, method, or pointer. Anything not under those possible types is currently not considered.
 * @tparam T Type to determine classification of
 */
template<typename T>
class TypeFinder {

    typedef const char _class[1];
    typedef const char _function[2];
    typedef const char _method[3];
    typedef const char _pointer[4];

    template<typename C, std::enable_if_t<std::is_class<C>::value, int> = 0>
    static _class& test() {return "";}

    template<typename C, std::enable_if_t<std::is_member_function_pointer<C>::value, int> = 0>
    static _method& test() {return "aa";}

    template<typename C, std::enable_if_t<std::is_function<C>::value || (std::is_pointer<C>::value && std::is_function<typename std::remove_pointer<C>::type>::value), int> = 0>
    static _function& test() {return "a";}

    template<typename C, std::enable_if_t<std::is_pointer<C>::value && !std::is_function<typename std::remove_pointer<C>::type>::value, int> = 0>
    static _pointer& test() {return "aaa";}

public:
    enum {
        cls = sizeof(test<T>()) == sizeof(_class),
        function = sizeof(test<T>()) == sizeof(_function),
        method = sizeof(test<T>()) == sizeof(_method),
        pointer = sizeof(test<T>()) == sizeof(_pointer),
        other = !cls && !function && !method && !pointer
    };
};

template<typename T, bool = std::is_pointer<T>::value>
struct MakePtr {
    typedef T type;

    static T make_ptr(T val);
};

template<typename T>
struct MakePtr<T, false> {
    typedef T* type;

    static T* make_ptr(T& val);
};

template<typename T, typename U>
struct __DerefPointer {
    typedef T type;
    static constexpr size_t depth = 0;
};

template<typename T, typename U>
struct __DerefPointer<T, U*> {
    typedef typename __DerefPointer<U, U>::type type;
    static constexpr size_t depth = __DerefPointer<U, U>::depth + 1;
};

template<typename T>
struct DerefPointer : public __DerefPointer<T, T> {};

template<typename>
struct FunctionTraits {
    enum {
        valid = 0,
        invalid = 1
    };
};

template<typename Ret, typename... Args>
struct FunctionTraits<Ret(Args...)> {
    typedef Ret return_type;
    
    typedef Ret(raw_type)(Args...);
    typedef Ret(*pointer_type)(Args...);
    
    static constexpr size_t num_args = sizeof...(Args);
    
    enum {
        valid = 1,
        invalid = 0
    };
};

template<typename Ret, typename... Args>
struct FunctionTraits<Ret(*)(Args...)> {
    typedef Ret return_type;
    
    typedef Ret(raw_type)(Args...);
    typedef Ret(*pointer_type)(Args...);
    
    static constexpr size_t num_args = sizeof...(Args);
    
    enum {
        valid = 1,
        invalid = 0
    };
};

template<typename>
struct MemberTraits {
    typedef void class_type;
    
    enum {
        valid = 0,
        invalid = 1
    };
};

template<typename Val, typename Cls>
struct MemberTraits<Val Cls::*> {
    typedef Cls class_type;
    typedef Val member_type;
    
    enum {
        valid = 1,
        invalid = 0
    };
};

template<typename>
struct MethodTraits {
    typedef void class_type;
    
    enum {
        valid = 0,
        invalid = 1
    };
};

template<typename Ret, typename Cls, typename... Args>
struct MethodTraits<Ret(Cls::*)(Args...)> {
    typedef Ret return_type;
    typedef Cls class_type;
    
    static constexpr size_t num_args = sizeof...(Args);
    
    enum {
        valid = 1,
        invalid = 0
    };
};

template<typename T>
class RawData {
    
    uchar* data;
    
public:
    
    static constexpr size_t size = sizeof(T);
    
    explicit RawData(T& obj);
    explicit RawData(T* obj);
    
    uchar& operator[](size_t pos);
    
    template<typename U>
    U get_value(size_t pos);
    
    template<typename U>
    void set_value(size_t pos, U val);
    
};

template<size_t... I>
struct TemplateRange {};

namespace VariadicRangeBuilder {
    
    template<size_t MIN, size_t N, size_t... I>
    struct range_builder;
    
    template<size_t MIN, size_t... I>
    struct range_builder<MIN, MIN, I...> {
        typedef TemplateRange<I...> range;
    };
    
    template<size_t MIN, size_t N, size_t... I>
    struct range_builder : public range_builder<MIN, N - 1, N - 1, I...> {};
    
}

template<typename... Args>
using VariadicRange = typename VariadicRangeBuilder::range_builder<0, sizeof...(Args)>::range;

}

#include "sfinae.tpp"

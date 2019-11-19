#pragma once

#include <type_traits>

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

}

#include "sfinae.tpp"

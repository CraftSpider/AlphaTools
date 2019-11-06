#pragma once

#include <type_traits>

namespace util {

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

}

#include "sfinae.tpp"

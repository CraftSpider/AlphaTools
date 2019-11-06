#pragma once

#include <type_traits>

namespace util {

template<typename T>
class TypeFinder {

    typedef char _class[1];
    typedef char _function[2];
    typedef char _method[3];
    typedef char _pointer[4];

    template<typename C, std::enable_if_t<std::is_class<C>::value, int> = 0>
    static _class& test();

    template<typename C, std::enable_if_t<std::is_member_function_pointer<C>::value, int> = 0>
    static _method& test();

    template<typename C, std::enable_if_t<std::is_pointer<C>::value && std::is_function<std::remove_pointer<C>::type>::value, int> = 0>
    static _function& test();

    template<typename C, std::enable_if_t<std::is_pointer<C>::vale && !std::is_function<std::remove_pointer<C>::type>::value, int> = 0>
    static _pointer& test();

public:
    enum {
        cls = sizeof(test()) == sizeof(_class),
        function = sizeof(test()) == sizeof(_function),
        method = sizeof(test()) == sizeof(_method),
        pointer = sizeof(test()) == sizeof(_pointer),
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

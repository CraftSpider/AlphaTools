
namespace testing {

template<typename T, bool B>
T __TestPtr<T, B>::make_ptr(T val) {
    return val;
}

template<typename T>
T* __TestPtr<T, false>::make_ptr(T&) {
    return new T();
}

}

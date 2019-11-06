
namespace util {

template<typename T, bool B>
T MakePtr<T, B>::make_ptr(T val) {
    return val;
}

template<typename T>
T* MakePtr<T, false>::make_ptr(T &val) {
    return &val;
}

}

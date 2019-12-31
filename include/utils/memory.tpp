
namespace util {

/**
 * \internal
 *
 * Type with a guaranteed sizeof(T), but is also guaranteed copyable/movable
 *
 * \tparam T Type to use
 */
template<typename T>
struct __Temp {
    uchar data[sizeof(T)];
};

template<typename T>
T* raw_copy(T& obj) {
    static_assert(sizeof(__Temp<T>) == sizeof(T));
    
    uchar *dst = reinterpret_cast<uchar*>(new __Temp<T>);
    uchar *src = reinterpret_cast<uchar*>(&obj);
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
    }
    
    return (T*)dst;
}

template<typename T>
T* raw_move(T& src) {
    static_assert(sizeof(__Temp<T>) == sizeof(T));
    
    uchar *dst = reinterpret_cast<uchar*>(new __Temp<T>);
    uchar *source = reinterpret_cast<uchar*>(&src);
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = source[i];
        source[i] = 0;
    }
    
    return (T*)dst;
}

template<typename T>
T& raw_move(T& src, T& dst) {
    uchar *dest = reinterpret_cast<uchar*>(&dst);
    uchar *source = reinterpret_cast<uchar*>(&src);
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dest[i] = source[i];
        source[i] = 0;
    }
    
    return *(T*)dest;
}

}

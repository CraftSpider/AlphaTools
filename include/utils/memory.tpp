
namespace util {

template<typename T>
struct __Temp {
    uchar data[sizeof(T)];
};

template<typename T>
T* raw_copy(T& obj) {
    static_assert(sizeof(__Temp<T>) == sizeof(T));
    
    uchar *dst = (uchar*)new __Temp<T>;
    uchar *src = (uchar*)&obj;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
    }
    
    return (T*)dst;
}

template<typename T>
T* raw_move(T& source) {
    static_assert(sizeof(__Temp<T>) == sizeof(T));
    
    uchar *dst = (uchar*)new __Temp<T>;
    uchar *src = (uchar*)&source;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
        src[i] = 0;
    }
    
    return (T*)dst;
}

template<typename T>
T& raw_move(T& source, T& dest) {
    uchar *dst = (uchar*)&dest;
    uchar *src = (uchar*)&source;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
        src[i] = 0;
    }
    
    return *(T*)dst;
}

}

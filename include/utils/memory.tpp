
namespace util {

template<typename T>
T* raw_copy(T& obj) {
    uchar *dst = new uchar[sizeof(T)];
    uchar *src = (uchar*)&obj;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
    }
    
    return (T*)dst;
}

template<typename T>
T* raw_move(T& source) {
    uchar dst = new uchar[sizeof(T)];
    uchar src = (uchar*)&source;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
        src[i] = 0;
    }
    
    return dst;
}

template<typename T>
T& raw_move(T& source, T& dest) {
    uchar dst = (uchar*)&dest;
    uchar src = (uchar*)&source;
    
    for (size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[i];
        src[i] = 0;
    }
    
    return *dst;
}

}

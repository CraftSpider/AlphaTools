
namespace util {

template<typename T>
T *reverse(T *arr, ulong len) {
    T *tmp = new T[len];
    for (ulong i = 0; i < len; ++i) {
        tmp[i] = arr[len - i];
    }
    for (ulong i = 0; i < len; ++i) {
        arr[i] = tmp[i];
    }
    delete[] tmp;
    return arr;
}

template<typename T>
T *endian_convert(T *arr, ulong len, ulong size) {
    T *tmp = new T[len];
    for (ulong i = 0; i < len; ++i) {
        tmp[(i + (size - 1)) - ((i % size) * 2)] = arr[i];
    }
    for (ulong i = 0; i < len; ++i) {
        arr[i] = tmp[i];
    }
    delete[] tmp;
    return arr;
}

}
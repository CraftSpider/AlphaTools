
#include <sstream>
#include <system_error>

namespace util {

template<typename T, bool B>
T __MakePtr<T, B>::make_ptr(const T& val) {
    return val;
}

template<typename T>
T* __MakePtr<T, false>::make_ptr(T& val) {
    return &val;
}

template<typename T>
RawData<T>::RawData(T& obj) {
    data = (uchar*)&obj;
}

template<typename T>
RawData<T>::RawData(T* obj) {
    data = (uchar*)obj;
}

template<typename T>
uchar& RawData<T>::operator[](size_t pos) {
    if (pos >= size) {
        std::stringstream s;
        s << "Invalid index " << pos;
        throw std::out_of_range(s.str());
    }
    return data[pos];
}

template<typename T>
template<typename U>
U& RawData<T>::get_value(size_t pos) {
    if (pos + sizeof(U) > size) {
        std::stringstream s;
        s << "Invalid index " << pos;
        throw std::out_of_range(s.str());
    }
    return *reinterpret_cast<U*>(data+pos);
}

template<typename T>
template<typename U>
void RawData<T>::set_value(size_t pos, const U& val) {
    if (pos + sizeof(U) > size) {
        std::stringstream s;
        s << "Invalid index " << pos;
        throw std::out_of_range(s.str());
    }
    *reinterpret_cast<U*>(data+pos) = val;
}

}

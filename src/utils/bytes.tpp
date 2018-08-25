namespace util {

template <Endian E>
uint btoi(const uchar* bytes, const ulong length) {
    return (uint)btol<E>(bytes, length);
}

template <Endian E>
int btoi(const char* bytes, const ulong length) {
    return (int)btol<E>(bytes, length);
}

template <Endian E>
ushort btos(const uchar* bytes, const ulong length) {
    return (ushort)btol<E>(bytes, length);
}

template <Endian E>
short btos(const char* bytes, const ulong length) {
    return (short)btol<E>(bytes, length);
}

template <Endian E>
uchar btoc(const uchar* bytes, const ulong length) {
    return (uchar)btol<E>(bytes, length);
}

template <Endian E>
char btoc(const char* bytes, const ulong length) {
    return (char)btol<E>(bytes, length);
}

}
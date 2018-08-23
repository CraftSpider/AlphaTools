
namespace util {

template <>
ulong next_ulong <BIG> (std::istream &file, const ulong length) {
    ulong out = 0;
    char *data = new char[length];
    file.read(data, length);
    for (ulong i = 0; i < length; ++i) {
        out += data[i] << (i * 4);
    }
    delete[] data;
    return out;
}

template <>
ulong next_ulong <LITTLE> (std::istream &file, const ulong length) {
    ulong out = 0;
    char *data = new char[length];
    file.read(data, length);
    for (ulong i = 0; i < length; ++i) {
        out += data[i] << ((length - i - 1) * 4);
    }
    delete[] data;
    return out;
}

template <Endian e>
uint next_uint(std::istream &file, const ulong length) {
    return (uint)next_ulong<e>(file, length);
}

template <Endian e>
ushort next_ushort(std::istream &file, const ulong length) {
    return (ushort)next_ulong<e>(file, length);
}

template <Endian e>
uchar next_uchar(std::istream &file, const ulong length) {
    return (uchar)next_ulong<e>(file, length);
}

}


#include "strmanip.h"
#include "arrays.h"
#include "bytes.h"
#include "generic.h"

namespace util {

template<Endian E>
ulong next_ulong(std::istream& file, const ulong length) {
    ulong out = 0;
    uchar* data = new uchar[length];
    file.read(reinterpret_cast<char*>(data), length);
    out = btol<E>(data, length);
    delete[] data;
    return out;
}

template<Endian E>
uint next_uint(std::istream& file, const ulong length) {
    return (uint)next_ulong<E>(file, length);
}

template<Endian E>
ushort next_ushort(std::istream& file, const ulong length) {
    return (ushort)next_ulong<E>(file, length);
}

template<Endian E>
uchar next_uchar(std::istream& file, const ulong length) {
    return (uchar)next_ulong<E>(file, length);
}

template<Endian E>
slong next_long(std::istream& file, const ulong length) {
    slong out = 0;
    char* data = new char[length];
    file.read(data, length);
    out = btol<E>(data, length);
    delete[] data;
    return out;
}

template<Endian E>
sint next_int(std::istream& file, const ulong length) {
    return (sint)next_long<E>(file, length);
}

template<Endian E>
sshort next_short(std::istream& file, const ulong length) {
    return (sshort)next_long<E>(file, length);
}

template<Endian E>
schar next_char(std::istream& file, const ulong length) {
    return (schar)next_long<E>(file, length);
}

template<Endian E>
float next_float(std::istream& file, const ulong length) {
    float data;
    file.read(reinterpret_cast<char*>(&data), length);
    if constexpr ((SysInfo::Endianness::little && E == Endian::BIG) || (SysInfo::Endianness::big && E == Endian::LITTLE)) {
        reverse(reinterpret_cast<char*>(&data), length);
    }
    return data;
}

template<Endian E>
double next_double(std::istream& file, const ulong length) {
    double data;
    file.read(reinterpret_cast<char*>(&data), length);
    if constexpr ((SysInfo::Endianness::little && E == Endian::BIG) || (SysInfo::Endianness::big && E == Endian::LITTLE)) {
        reverse(reinterpret_cast<char*>(&data), length);
    }
    return data;
}

template<Endian E>
std::string next_string(std::istream& file, const ulong length) {
    if (length == 0) {
        std::string out;
        char c;
        do {
            file.read(&c, 1);
            out += c;
        } while (c != '\0');
        if constexpr ((SysInfo::Endianness::little && E == Endian::LITTLE) || (SysInfo::Endianness::big && E == Endian::BIG)) {
            out = reverse(out);
        }
        return out;
    } else {
        char* cstr = new char[length];
        file.read(cstr, length);
        if constexpr ((SysInfo::Endianness::little && E == Endian::LITTLE) || (SysInfo::Endianness::big && E == Endian::BIG)) {
            reverse(cstr, length);
        }
        std::string out = std::string(cstr, length);
        delete[] cstr;
        return out;
    }
}

template<Endian E>
void write_ulong(std::ostream& file, const ulong out, const ulong length) {
    const uchar* to_write = ltob<E>(out, length);
    file.write((char*)to_write, length);
    delete[] to_write;
}

template<Endian E>
void write_uint(std::ostream& file, const uint out, const ulong length) {
    write_ulong<E>(file, out, length);
}

template<Endian E>
void write_ushort(std::ostream& file, const ushort out, const ulong length) {
    write_ulong<E>(file, out, length);
}

template<Endian E>
void write_uchar(std::ostream& file, const uchar out, const ulong length) {
    write_ulong<E>(file, out, length);
}

template<Endian E>
void write_long(std::ostream& file, const slong out, const ulong length) {
    const char* to_write = ltob<E>(out, length);
    file.write(to_write, length);
    delete[] to_write;
}

template<Endian E>
void write_int(std::ostream& file, const sint out, const ulong length) {
    write_long<E>(file, out, length);
}

template<Endian E>
void write_short(std::ostream& file, const sshort out, const ulong length) {
    write_long<E>(file, out, length);
}

template<Endian E>
void write_char(std::ostream& file, const schar out, const ulong length) {
    write_long<E>(file, out, length);
}

template<Endian E>
void write_float(std::ostream& file, float out, const ulong length) {
    if constexpr ((SysInfo::Endianness::little && E == Endian::BIG) || (SysInfo::Endianness::big && E == Endian::LITTLE)) {
        reverse(reinterpret_cast<char*>(&out), length);
    }
    file.write(reinterpret_cast<char*>(&out), length);
}

template<Endian E>
void write_double(std::ostream& file, double out, const ulong length) {
    if constexpr ((SysInfo::Endianness::little && E == Endian::BIG) || (SysInfo::Endianness::big && E == Endian::LITTLE)) {
        reverse(reinterpret_cast<char*>(&out), length);
    }
    file.write(reinterpret_cast<char*>(&out), length);
}

template<Endian E>
void write_string(std::ostream& file, const std::string& out, ulong length) {
    if (length == 0) {
        length = out.size();
    }
    if constexpr ((SysInfo::Endianness::little && E == Endian::LITTLE) || (SysInfo::Endianness::big && E == Endian::BIG)) {
        char* data = new char[length];
        copy(out.c_str(), data, length);
        file.write(reverse(data, length), length);
    } else {
        file.write(out.c_str(), length);
    }
}

}


#include "bytes.h"

namespace util {

bool get_bit(const uchar *data, const ulong pos) {
    ulong loc = pos / 8;
    return (bool)(data[loc] & (1 << (7 - (pos % 8))));
}

ulong get_range(const uchar *data, const ulong start, const ulong end) {
    uint out = 0;
    ulong num_bits = (end - start) + 1;
    for (ulong i = start, j = 1; i <= end; ++i, ++j) {
        out += 2 << (num_bits - j)* get_bit(data, i);
    }
    return out;
}

long get_signed_range(const uchar *data, const ulong start, const ulong end) {
    ulong value = get_range(data, start, end);
    ulong num_bits = end - start;
    ulong mask = 1ul << num_bits;
    return -((long)(value & mask) + (long)(value & (mask - 1)));
}

template <>
ulong btol <BIG> (const uchar* bytes, const ulong length) {
    ulong out = 0;
    for (ulong i = 0; i < length; ++i) {
        out |= (ulong)bytes[i] << ((length - i - 1) * 8);
    }
    return out;
}

template <>
ulong btol <LITTLE> (const uchar* bytes, const ulong length) {
    ulong out = 0;
    for (ulong i = 0; i < length; ++i) {
        out |= (ulong)bytes[i] << (i * 8);
    }
    return out;
}

template <>
long btol <BIG> (const char* bytes, const ulong length) {
    long out = 0;
    for (ulong i = 0; i < length; ++i) {
        out |= (long)bytes[i] << ((length - i - 1) * 8);
    }
    return out;
}

template <>
long btol <LITTLE> (const char* bytes, const ulong length) {
    long out = 0;
    for (ulong i = 0; i < length; ++i) {
        out |= (long)bytes[i] << (i * 8);
    }
    return out;
}

template <>
uchar* ltob <BIG> (const ulong val, const ulong length) {
    uchar *output = new uchar[length]();
    for (ulong i = 0; i < length; ++i) {
        output[i] = (uchar)(val >> (8 * (length - i - 1)));
    }
    return output;
}

template <>
uchar* ltob <LITTLE> (const ulong val, const ulong length) {
    uchar *output = new uchar[length]();
    for (ulong i = 0; i < length; ++i) {
        output[i] = (uchar)(val >> (8 * i));
    }
    return output;
}

}
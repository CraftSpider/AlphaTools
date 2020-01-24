
#include "utils/bytes.h"

namespace util {

bool get_bit(const uchar* data, const ulong pos) {
    return (bool)(data[pos / 8] & (1u << (7 - (pos % 8))));
}

ulong get_range(const uchar* data, const ulong start, const ulong end) {
    uint out = 0;
    ulong num_bits = (end - start) + 1;
    for (ulong i = start, j = 1; i <= end; ++i, ++j) {
        out += (1u << (num_bits - j)) * get_bit(data, i);
    }
    return out;
}

long get_signed_range(const uchar* data, const ulong start, const ulong end) {
    ulong value = get_range(data, start, end);
    ulong num_bits = (end - start) + 1;
    if (value & ((ulong)1 << (num_bits - 1))) {
        ulong mask = ~0ul << num_bits;
        return (long)(value | mask);
    } else {
        return (long)(value);
    }
}

template <>
ulong btol <BIG> (const uchar* bytes, const ulong start, const ulong end) {
    ulong out = 0;
    ulong length = end - start - 1;
    for (ulong i = start; i < end; ++i) {
        out |= (ulong)bytes[i] << ((length - i) * 8);
    }
    return out;
}

template <>
ulong btol <LITTLE> (const uchar* bytes, const ulong start, const ulong end) {
    ulong out = 0;
    for (ulong i = start; i < end; ++i) {
        out |= (ulong)bytes[i] << (i * 8);
    }
    return out;
}

template <>
slong btol <BIG> (const char* bytes, const ulong start, const ulong end) {
    slong out = 0;
    ulong length = end - start - 1;
    for (ulong i = start; i < end; ++i) {
        out |= ((ulong)bytes[i] & 0xFFu) << ((length - i) * 8);
    }
    return out;
}

template <>
slong btol <LITTLE> (const char* bytes, const ulong start, const ulong end) {
    slong out = 0;
    for (ulong i = start; i < end; ++i) {
        out |= ((ulong)bytes[i] & 0xFFu) << (i * 8);
    }
    return out;
}

template <>
uchar* ltob <BIG> (const ulong val, const ulong length) {
    uchar* output = new uchar[length]();
    for (ulong i = 0; i < length; ++i) {
        output[i] = (uchar)(val >> (8 * (length - i - 1)));
    }
    return output;
}

template <>
uchar* ltob <LITTLE> (const ulong val, const ulong length) {
    uchar* output = new uchar[length]();
    for (ulong i = 0; i < length; ++i) {
        output[i] = (uchar)(val >> (8 * i));
    }
    return output;
}

template <>
char* ltob <BIG> (const slong val, const ulong length) {
    char* output = new char[length];
    for (ulong i = 0; i < length; ++i) {
        output[i] = (char)(val >> (8 * (length - i - 1)));
    }
    return output;
}

template <>
char* ltob <LITTLE> (const slong val, const ulong length) {
    char* output = new char[length];
    for (ulong i = 0; i < length; ++i) {
        output[i] = (char)(val >> (8 * i));
    }
    return output;
}

}
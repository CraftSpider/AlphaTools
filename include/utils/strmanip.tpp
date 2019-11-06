
#include <sstream>
#include "bytes.h"
#include "arrays.h"

namespace util {

template<Endian E>
std::string btoh(const uchar* val, const ulong length, const bool prefix, const bool pad) {
    std::stringstream out;
    bool start = true;
    if (prefix)
        out << "0x";
    
    out << std::hex << std::uppercase;
    for (ulong i = 0; i < length; ++i) {
        ulong pos;
        if constexpr (E == LITTLE) {
            pos = (length - 1) - i;
        } else {
            pos = i;
        }
        
        if (val[pos] == 0 && !pad && start) {
            continue;
        }
        
        if (val[pos] < 0x10 && (pad || !start))
            out << "0";
        
        out << (uint)val[pos];
        start = false;
    }
    
    if (out.str().empty() || out.str() == "0x") {
        out << "0";
    }
    return out.str();
}

template<Endian E>
std::string btoh(const char* val, const ulong length, const bool prefix, const bool pad) {
    std::stringstream out;
    bool start = true;
    if (prefix)
        out << "0x";
    
    out << std::hex << std::uppercase;
    for (ulong i = 0; i < length; ++i) {
        ulong pos;
        if constexpr (E == LITTLE) {
            pos = (length - 1) - i;
        } else {
            pos = i;
        }
        
        if (val[pos] == 0 && !pad && start) {
            continue;
        }
        
        uchar outc = (uchar)val[pos];
        if (outc < 0x10 && (pad || !start))
            out << "0";
        
        out << (uint)outc;
        start = false;
    }
    
    if (out.str().empty() || out.str() == "0x") {
        out << "0";
    }
    return out.str();
}

template<Endian E>
std::string ltoh(ulong val, bool prefix, bool pad) {
    uchar* temp = ltob(val);
    std::string out = btoh<E>(temp, 8, prefix, pad);
    delete[] temp;
    return out;
}

template<Endian E>
std::string ltoh(slong val, bool prefix, bool pad) {
    std::stringstream out;
    if (val < 0) {
        out << "-";
        val = -val;
    }
    char* temp = ltob(val);
    out << btoh<E>(temp, 8, prefix, pad);
    delete[] temp;
    return out.str();
    
}

template<Endian E>
std::string itoh(uint val, bool prefix, bool pad) {
    uchar* temp = itob(val);
    std::string out = btoh<E>(temp, 4, prefix, pad);
    delete[] temp;
    return out;
}

template<Endian E>
std::string itoh(int val, bool prefix, bool pad) {
    std::stringstream out;
    if (val < 0) {
        out << "-";
        val = -val;
    }
    char* temp = itob(val);
    out << btoh<E>(temp, 4, prefix, pad);
    delete[] temp;
    return out.str();
}

template<Endian E>
std::string stoh(ushort val, bool prefix, bool pad) {
    uchar* temp = stob(val);
    std::string out = btoh<E>(temp, 2, prefix, pad);
    delete[] temp;
    return out;
}

template<Endian E>
std::string stoh(short val, bool prefix, bool pad) {
    std::stringstream out;
    if (val < 0) {
        out << "-";
        val = -val;
    }
    char* temp = stob(val);
    out << btoh<E>(temp, 2, prefix, pad);
    delete[] temp;
    return out.str();
}

template<Endian E>
std::string ctoh(uchar val, bool prefix, bool pad) {
    uchar* temp = ctob(val);
    std::string out = btoh<E>(temp, 1, prefix, pad);
    delete[] temp;
    return out;
}

template<Endian E>
std::string ctoh(char val, bool prefix, bool pad) {
    std::stringstream out;
    if (val < 0) {
        out << "-";
        val = -val;
    }
    char* temp = ctob(val);
    out << btoh<E>(temp, 1, prefix, pad);
    delete[] temp;
    return out.str();
}

}
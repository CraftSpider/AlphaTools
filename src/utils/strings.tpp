
#include <sstream>

namespace util {

template <Endian E>
std::string ltoh(const ulong val) {
    std::stringstream out;
    out << "0x";
    out << std::hex << std::uppercase << val;
    return out.str();
}

template <Endian E>
std::string ltoh(const long val) {
    std::stringstream out;
    if (val < 0) {
        out << "-";
    }
    out << "0x";
    out << std::hex << std::uppercase << (val >= 0 ? val : -val);
    return out.str();
}

}
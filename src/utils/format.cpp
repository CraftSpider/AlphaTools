
#include "types.h"
#include "utils/format.h"
#include "utils/strmanip.h"

namespace util {

template<>
std::string spec_handler <int> (std::string spec, int* arg) {
    std::stringstream out;
    
    bool pref = false;
    if (spec.find('0') != std::string::npos)
        pref = true;
    if (spec.find('x') != std::string::npos)
        out << (pref ? "0x" : "") << std::hex;
    else if (spec.find('X') != std::string::npos)
        out << (pref ? "0x" : "") << std::hex << std::uppercase;
    else if (spec.find('o') != std::string::npos)
        out << (pref ? "0o" : "") << std::oct;
    
    out << *arg;
    return out.str();
}

template<>
std::string spec_handler <std::string> (std::string spec, std::string* arg) {
    std::stringstream out;
    std::string str = *arg;
    
    if (spec.find('u') != std::string::npos) {
        str = util::to_uppercase(str);
    } else if (spec.find('l') != std::string::npos) {
        str = util::to_lowercase(str);
    }
    
    if (spec.find('n') != std::string::npos)
        out << str.size();
    else
        out << str;
    
    return out.str();
}

template<>
std::string spec_handler <const char*> (std::string spec, const char** arg) {
    std::string temp = std::string(*arg);
    return spec_handler(spec, &temp);
}

template<>
std::string spec_handler <uchar*> (std::string spec, uchar** arg) {
    if (spec == "") {
        return "";
    }
    
    const uchar* bytes = *arg;
    std::stringstream out;
    
    size_t num_start = spec.find_first_of("1234567890");
    size_t comma_pos = spec.find(',');
    std::string mods = spec.substr(0, num_start);
    int start = std::stoi(spec.substr(num_start, comma_pos));
    int end = std::stoi(spec.substr(comma_pos + 1));
    
    uint mod_mask = 0;
    if (mods.find('s') != std::string::npos) {
        mod_mask |= 0b10u;
    }
    if (mods.find('x') != std::string::npos) {
        mod_mask |= 0b1u;
    }
    
    if (mods.find('a') != std::string::npos) {
        mod_mask |= 0b1010u;
    }
    if (mods.find('X') != std::string::npos) {
        mod_mask |= 0b101u;
    }
    
    if (mod_mask & 0b100u) {
        out << std::uppercase;
    }
    
    if (mod_mask & 0b10u) {
        slong result = util::get_signed_range(bytes, start, end);
        if (mod_mask & 0b1000u) {
            result = std::abs(result);
        }
        if (mod_mask & 0b1u) {
            out << util::ltoh(result);
        } else {
            out << result;
        }
    } else {
        ulong result = util::get_range(bytes, start, end);
        if (mod_mask & 0b1u) {
            out << util::ltoh(result);
        } else {
            out << result;
        }
    }
    
    return out.str();
}

}

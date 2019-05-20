
#include <sstream>
#include <cstdarg>
#include <csetjmp>
#include <csignal>

#include "format.h"
#include "utils/bytes.h"
#include "utils/strmanip.h"

static jmp_buf buf;
void (*old_sig)(int);

format_error::format_error(const std::string &msg) : std::runtime_error(msg) {}

template<typename T>
const T spec_cast(const void* input) {
    return *(const T*)input;
}

/**
 * Format an integer spec. Viable options are:
 * x: Lowercase hex
 * X: Uppercase hex
 * o: octal
 * 0: Prefix with literal type (0x or 0o)
 * @param spec Format spec string
 * @param val value to format
 * @return formatted string
 */
std::string int_spec(std::string spec, const void* val) {
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
    out << spec_cast<int>(val);
    return out.str();
}

std::string long_spec(std::string spec, const void* val) {
    // TODO: Add long specification
    std::stringstream out;
    out << spec_cast<long>(val);
    return out.str();
}

std::string float_spec(std::string spec, const void* val) {
    // TODO: Add float specification
    std::stringstream out;
    out << spec_cast<float>(val);
    return out.str();
}

std::string double_spec(std::string spec, const void* val) {
    // TODO: Add double specification
    std::stringstream out;
    out << spec_cast<double>(val);
    return out.str();
}

std::string string_spec(std::string spec, const void* val) {
    // TODO: Add string specification
    return std::string(spec_cast<char*>(val));
}

std::string byte_spec(std::string spec, const void* val) {
    if (spec == "") {
        return "";
    }
    
    const uchar* bytes = spec_cast<uchar*>(val);
    std::stringstream out;
    
    int num_start = spec.find_first_of("1234567890");
    int comma_pos = spec.find(',');
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

std::string object_handler(std::string spec, const void* val) {
    std::stringstream out;
    if (!setjmp(buf)) {
        const Formattable* form = spec_cast<Formattable*>(val);
        out << form->__format__(std::move(spec));
    } else {
        std::signal(SIGSEGV, old_sig);
        throw format_error("Non-formattable object passed to spec o");
    }
    return out.str();
}

std::map<char, format_handler> __Handlers::handlers = {
    {'i', &int_spec},
    {'l', &long_spec},
    {'f', &float_spec},
    {'d', &double_spec},
    {'s', &string_spec},
    {'b', &byte_spec},
    {'o', &object_handler}
};

std::map<char, char> __Handlers::size = {
    {'i', sizeof(int)},
    {'l', sizeof(long)},
    {'f', sizeof(double)},
    {'d', sizeof(double)},
    {'s', sizeof(char*)},
    {'b', sizeof(char*)},
    {'o', sizeof(void*)}
};

static void format_signal_handler(int) {
    longjmp(buf, 1);
}

std::string format(std::string pattern, ...) {
    old_sig = std::signal(SIGSEGV, format_signal_handler);
    
    bool escaped = false, in_spec = false;
    std::stringstream out, spec;
    va_list args;
    va_start(args, pattern);
    
    for (auto c : pattern) {
        if (escaped) {
            out << c;
            escaped = false;
        } else if (in_spec) {
            if (c == '}') {
                in_spec = false;
                std::string s = spec.str();
                int colon_pos = s.find(':');
                char type = s[0];
                s = s.substr(colon_pos + 1);
                
                format_handler handler = __Handlers::handlers[type];
                char size = __Handlers::size[type];
                if (handler) {
                    uint64_t val;
                    if (size <= 4) {
                        val = va_arg(args, uint32_t);
                    } else {
                        val = va_arg(args, uint64_t);
                    }
                    out << handler(s, &val);
                } else {
                    std::signal(SIGSEGV, old_sig);
                    throw format_error("Unrecognized formatting spec");
                }
                std::stringstream().swap(spec);
            } else {
                spec << c;
            }
        } else {
            if (c == '\\') {
                escaped = true;
            } else if (c == '{') {
                in_spec = true;
            } else {
                out << c;
            }
        }
    }
    
    std::signal(SIGSEGV, old_sig);
    
    return out.str();
}

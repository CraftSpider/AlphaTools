
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdarg>
#include <csetjmp>
#include <csignal>

#include "format.h"
#include "utils/bytes.h"
#include "utils/strmanip.h"

static jmp_buf buf;

static void format_signal_handler(int) {
    longjmp(buf, 1);
}

void Formattable::__is_formattable__() const {}

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
 * @param val Value to format
 * @return Formatted string
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

/**
 * Format a character string spec. Viable options are:
 * u: Uppercase
 * l: Lowercase
 * n: Replace with length of string
 * @param spec Format spec string
 * @param val Value to format
 * @return Formatted string
 */
std::string string_spec(std::string spec, const void* val) {
    std::stringstream out;
    std::string str(spec_cast<char*>(val));
    
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

std::string byte_spec(std::string spec, const void* val) {
    if (spec == "") {
        return "";
    }
    
    const uchar* bytes = spec_cast<uchar*>(val);
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

std::string object_handler(std::string spec, const void* val) {
    std::string result;
    const Formattable* form = spec_cast<Formattable*>(val);
    
    void (*old_sig)(int) = std::signal(SIGSEGV, format_signal_handler);
    if (!setjmp(buf)) {
        form->__is_formattable__();
    } else {
        std::signal(SIGSEGV, old_sig);
        throw format_error("Non-formattable object passed to spec o");
    }
    std::signal(SIGSEGV, old_sig);
    
    return form->__format__(std::move(spec));
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

std::map<char, size_t> __Handlers::size = {
    {'i', sizeof(int)},
    {'l', sizeof(long)},
    {'f', sizeof(double)},
    {'d', sizeof(double)},
    {'s', sizeof(char*)},
    {'b', sizeof(char*)},
    {'o', sizeof(void*)}
};

struct Spec {
    std::string type, args;
    int pos;
};

bool add_format_handler(char spec, format_handler handler, size_t size) {
    if (__Handlers::handlers.count(spec))
        return false;
    __Handlers::handlers[spec] = handler;
    __Handlers::size[spec] = size;
    return true;
}

bool remove_format_handler(char spec) {
    if (!__Handlers::handlers.count(spec))
        return false;
    __Handlers::handlers.erase(spec);
    __Handlers::size.erase(spec);
    return true;
}

std::string format(std::string pattern, ...) {
    bool escaped = false, in_spec = false;
    std::stringstream out, spec_stream;
    va_list args;
    va_start(args, pattern);
    
    std::vector<Spec> spec_cache = std::vector<Spec>();
    
    // Generate a list of format specifications
    int cur_pos = 0;
    
    for (auto c : pattern) {
        if (escaped) {
            continue;
        } else if (in_spec) {
            if (c == '}') {
                
                std::string spec_str = spec_stream.str();
                ulong colon_pos = spec_str.find(':');
    
                std::string def = spec_str.substr(0, colon_pos);
                
                if (colon_pos == std::string::npos) {
                    spec_str = "";
                } else {
                    spec_str = spec_str.substr(colon_pos + 1);
                }
                
                char type = def[0];
                int pos;
                if (def.size() > 1) {
                    pos = std::stoi(def.substr(1));
                } else {
                    pos = cur_pos;
                    cur_pos++;
                }
                
                Spec spec = Spec {std::string(1, type), spec_str, pos};
                spec_cache.emplace_back(spec);
                
                in_spec = false;
                std::stringstream().swap(spec_stream);
            } else {
                spec_stream << c;
            }
        } else if (c == '\\') {
            escaped = true;
        } else if (c == '{') {
            in_spec = true;
        }
    }
    
    // Read in each argument, as implied by the specifications
    std::map<int, int> sizes_cache;
    for (Spec spec : spec_cache) {
        if (!sizes_cache.count(spec.pos)) {
            sizes_cache[spec.pos] = __Handlers::size[spec.type[0]];
        }
    }
    
    std::vector<ulong> arg_cache = std::vector<ulong>();
    for (ulong i = 0; i < sizes_cache.size(); ++i) {
        if (!sizes_cache.count(i)) {
            throw format_error("No reference for argument position");
        }
        
        ulong val;
        if (sizes_cache[i] <= 4) {
            val = va_arg(args, uint);
        } else {
            val = va_arg(args, ulong);
        }
        arg_cache.emplace_back(val);
    }
    
    // Generate output from specifications
    
    int count = 0;
    
    for (auto c : pattern) {
        if (escaped) {
            out << c;
            escaped = false;
        } else if (in_spec) {
            if (c == '}') {
                in_spec = false;
                
                Spec spec = spec_cache[count++];
                
                format_handler handler = __Handlers::handlers[spec.type[0]];
                
                if (handler) {
                    out << handler(spec.args, &arg_cache[spec.pos]);
                } else {
                    throw format_error("Unrecognized formatting spec: " + spec.type);
                }
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
    
    return out.str();
}

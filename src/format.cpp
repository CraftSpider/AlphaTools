
#include <sstream>
#include <cstdarg>
#include <csetjmp>
#include <csignal>

#include "format.h"

static jmp_buf buf;

format_error::format_error(const std::string &msg) : std::runtime_error(msg) {}

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
    out << *(int*)val;
    return out.str();
}

std::string float_spec(std::string spec, const void* val) {
    // TODO
    std::stringstream out;
    out << *(float*)val;
    return out.str();
}

std::string double_spec(std::string spec, const void* val) {
    // TODO
    std::stringstream out;
    out << *(double*)val;
    return out.str();
}

std::string string_spec(std::string spec, const void* val) {
    // TODO
    return std::string((char*)val);
}

std::string object_handler(std::string spec, const void* val) {
    std::stringstream out;
    if (!setjmp(buf)) {
        Formattable* form = *(Formattable**)val;
        out << form->__format__(spec);
    } else {
        throw format_error("Non-formattable object passed to spec o");
    }
    return out.str();
}

std::map<char, format_handler> __Handlers::handlers = {
    {'i', &int_spec},
    {'f', &float_spec},
    {'d', &double_spec},
    {'s', &string_spec},
    {'o', &object_handler}
};

std::map<char, char> __Handlers::size = {
    {'i', sizeof(int)},
    {'l', sizeof(long)},
    {'f', sizeof(double)},
    {'d', sizeof(double)},
    {'s', sizeof(char*)},
    {'o', sizeof(void*)}
};

static void format_signal_handler(int) {
    longjmp(buf, 1);
}

std::string format(const std::string &pattern, ...) {
    void (*old_sig)(int) = std::signal(SIGSEGV, format_signal_handler);
    
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
                char type = s[0];
                s = s.substr(1, s.size());
                
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
            }
        }
    }
    
    std::signal(SIGSEGV, old_sig);
    
    return out.str();
}


#include <sstream>
#include <cstdarg>
#include "format.h"

std::string int_spec(std::string spec, int val) {
    // TODO
    return spec;
}

std::string float_spec(std::string spec, float val) {
    // TODO
    return spec;
}

std::string double_spec(std::string spec, double val) {
    // TODO
    return spec;
}

std::string string_spec(std::string spec, char* val) {
    // TODO
    return std::string(val);
}

std::string format(std::string pattern, ...) {
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
                if (s[0] == 'i') {
                    out << int_spec(s, va_arg(args, int));
                } else if (s[0] == 'd') {
                } else if (s[0] == 'f') {
                } else if (s[0] == 's') {
                } else if (s[0] == 'o') {
                    out << va_arg(args, Formattable*)->__format__(s);
                } else {
                    throw std::runtime_error("Invalid formatting spec");
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
    return out.str();
}

#include <sstream>
#include <cstdarg>
#include <csetjmp>
#include "format.h"

class BadObject : public Formattable {
    void* ptr = nullptr;
public:
    void set_ptr(void* ptr) {
        this->ptr = ptr;
    }
    
    std::string __format__(std::string spec) override {
        std::stringstream out;
        out << "[[NON-FORMATTABLE OBJECT " << ptr << "]]";
        return out.str();
    }
};

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
std::string int_spec(std::string spec, long val) {
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
    out << val;
    return out.str();
}

std::string float_spec(std::string spec, float val) {
    // TODO
    std::stringstream out;
    out << val;
    return out.str();
}

std::string double_spec(std::string spec, double val) {
    // TODO
    std::stringstream out;
    out << val;
    return out.str();
}

std::string string_spec(std::string spec, char* val) {
    // TODO
    return std::string(val);
}

static jmp_buf buf;

static void format_handler(int signo) {
    longjmp(buf, 1);
}

std::string format(std::string pattern, ...) {
    signal(SIGSEGV, format_handler);
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
                if (type == 'i') {
                    out << int_spec(s, va_arg(args, long));
                } else if (type == 'd') {
                    out << double_spec(s, va_arg(args, double));
                } else if (type == 'f') {
                    out << float_spec(s, (float)va_arg(args, double));
                } else if (type == 's') {
                    out << string_spec(s, va_arg(args, char*));
                } else if (type == 'o') {
                    Formattable* form = va_arg(args, Formattable*);
                    if (!setjmp(buf)) {
                        out << form->__format__(s);
                    } else {
                        BadObject object = BadObject();
                        object.set_ptr(form);
                        out << object.__format__(s);
                    }
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
    signal(SIGSEGV, SIG_DFL);
    return out.str();
}